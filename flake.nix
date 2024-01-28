{
  description = "Build a cargo project";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

    crane = {
      url = "github:ipetkov/crane";
      inputs.nixpkgs.follows = "nixpkgs";
    };

    rust-overlay = {
      url = "github:oxalica/rust-overlay";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        flake-utils.follows = "flake-utils";
      };
    };

    flake-utils.url = "github:numtide/flake-utils";

    advisory-db = {
      url = "github:rustsec/advisory-db";
      flake = false;
    };
  };

  outputs = { self, nixpkgs, crane, rust-overlay, flake-utils, advisory-db, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [ (import rust-overlay) ];
        };

        rustToolchain = pkgs.rust-bin.selectLatestNightlyWith (toolchain: toolchain.default.override {
          extensions = [ "rust-src" ];
          targets = [ "x86_64-unknown-linux-gnu" ];
        });

        craneLib = (crane.mkLib pkgs).overrideToolchain rustToolchain;
        src = craneLib.cleanCargoSource (craneLib.path ./.);

        pname = "just_enough_mod";
        version = "0.0.0";

        buildDeps = (with pkgs; [ pkg-config makeWrapper clang lld mold ]);

        runtimeDeps = (with pkgs;
          [ libxkbcommon alsa-lib udev vulkan-loader wayland ]
          ++ (with xorg; [ libXcursor libXrandr libXi libX11 ]));

        # Build the actual crate itself, reusing the dependency
        # artifacts from above.
        my-crate = craneLib.buildPackage rec {
          inherit src pname version;

          nativeBuildInputs = buildDeps;
          buildInputs = runtimeDeps;

          postInstall = ''
            wrapProgram $out/bin/${pname} \
              --prefix LD_LIBRARY_PATH : ${
                pkgs.lib.makeLibraryPath runtimeDeps
              } 
            mkdir -p $out/bin/assets
            cp -a just_enough_mod/assets $out/bin
          '';
        };
      in {
        checks = {
          # Build the crate as part of `nix flake check` for convenience
          inherit my-crate;

          # Run clippy (and deny all warnings) on the crate source,
          # again, resuing the dependency artifacts from above.
          #
          # Note that this is done as a separate derivation so that
          # we can block the CI if there are issues here, but not
          # prevent downstream consumers from building our crate by itself.
          # my-crate-clippy = craneLib.cargoClippy {
          #   cargoClippyExtraArgs = "--all-targets -- --deny warnings";
          # };

          # Check formatting
          my-crate-fmt = craneLib.cargoFmt { inherit src pname version; };

          # Audit dependencies
          my-crate-audit =
            craneLib.cargoAudit { inherit src pname version advisory-db; };

          # Audit licenses
          my-crate-deny = craneLib.cargoDeny { inherit src pname version; };

        };

        packages = { default = my-crate; };

        apps.default = flake-utils.lib.mkApp { drv = my-crate; };

        devShells.default = craneLib.devShell {
          # Inherit inputs from checks.
          checks = self.checks.${system};

          RUST_SRC_PATH = "${pkgs.rustPlatform.rustLibSrc}";
          # Additional dev-shell environment variables can be set directly
          LD_LIBRARY_PATH = "${pkgs.lib.makeLibraryPath runtimeDeps}";

          # Extra inputs can be added here; cargo and rustc are provided by default.
          packages = with pkgs; [
          ];

          nativeBuildInputs = with pkgs; [
              pkg-config
          ];
        };
      });
}
