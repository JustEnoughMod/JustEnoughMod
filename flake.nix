{
  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    pre-commit-hooks.url = "github:cachix/pre-commit-hooks.nix";
    bgfx = {
      url = "https://github.com/LDprg/bgfx.meson";
      flake = false;
      type = "git";
      submodules = true;
    };
    dylib = {
      url = "https://github.com/LDprg/dylib.meson";
      flake = false;
      type = "git";
      submodules = true;
    };
  };

  outputs = { self, nixpkgs, flake-utils, pre-commit-hooks, bgfx, dylib }:
    let overlayPackage = import ./overlay.nix { inherit bgfx dylib; };
    in flake-utils.lib.eachDefaultSystem (system:
      let
        overlayShell = _: prev: {
          JustEnoughMod-shell = prev.JustEnoughMod.overrideAttrs (_: {
            inherit (self.checks.${system}.pre-commit-check) shellHook;
          });
        };

        pkgs = import nixpkgs {
          inherit system;
          overlays = [ overlayPackage overlayShell ];
        };
      in with pkgs; {
        checks = {
          pre-commit-check = pre-commit-hooks.lib.${system}.run {
            src = ./.;
            hooks = {
              check-added-large-files = {
                enable = true;
                name = "check-added-large-files";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/check-added-large-files";
              };
              check-case-conflicts = {
                enable = true;
                name = "check-case-conflicts";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/check-case-conflict";
                types = [ "file" ];
              };
              check-executables-have-shebangs = {
                enable = true;
                name = "check-executables-have-shebangs";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/check-executables-have-shebangs";
                types = [ "text" "executable" ];
              };
              check-json = {
                enable = true;
                name = "check-json";
                entry = "${python3Packages.pre-commit-hooks}/bin/check-json";
                types = [ "json" ];
              };
              check-merge-conflicts = {
                enable = true;
                name = "check-merge-conflicts";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/check-merge-conflict";
                types = [ "text" ];
              };
              check-shebang-scripts-are-executable = {
                enable = true;
                name = "check-shebang-scripts-are-executable";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/check-shebang-scripts-are-executable";
                types = [ "text" ];
              };
              check-symlinks = {
                enable = true;
                name = "check-symlinks";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/check-symlinks";
                types = [ "symlink" ];
              };
              check-toml = {
                enable = true;
                name = "check-toml";
                entry = "${python3Packages.pre-commit-hooks}/bin/check-toml";
                types = [ "toml" ];
              };
              check-xml = {
                enable = true;
                name = "check-xml";
                entry = "${python3Packages.pre-commit-hooks}/bin/check-xml";
                types = [ "xml" ];
              };
              check-yaml = {
                enable = true;
                name = "check-yaml";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/check-yaml --multi";
                types = [ "yaml" ];
              };
              detect-private-keys = {
                enable = true;
                name = "detect-private-keys";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/detect-private-key";
                types = [ "text" ];
              };
              destroyed-symlinks = {
                enable = true;
                name = "destroyed-symlinks";
                description = "Detect the presence of private keys.";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/destroyed-symlinks";
                types = [ "text" ];
              };
              end-of-file-fixer = {
                enable = true;
                name = "end-of-file-fixer";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/end-of-file-fixer";
                types = [ "text" ];
              };
              fix-byte-order-marker = {
                enable = true;
                name = "fix-byte-order-marker";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/fix-byte-order-marker";
                types = [ "text" ];
              };
              mixed-line-endings = {
                enable = true;
                name = "mixed-line-endings";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/mixed-line-ending";
                types = [ "text" ];
              };
              pretty-format-json = {
                enable = true;
                name = "pretty-format-json";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/pretty-format-json --autofix";
                types = [ "json" ];
              };
              sort-simple-yaml = {
                enable = true;
                name = "sort-simple-yaml";
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/sort-simple-yaml";
                files = "(\\.yaml$)|(\\.yml$)";
              };
              trim-trailing-whitespace = {
                enable = true;
                name = "trim-trailing-whitespace";
                types = [ "text" ];
                entry =
                  "${python3Packages.pre-commit-hooks}/bin/trailing-whitespace-fixer";
              };

              deadnix.enable = true;
              nil.enable = true;
              nixfmt.enable = true;
              statix.enable = true;

              shfmt.enable = true;

              clang-format.enable = true;
            };
          };
        };

        devShells.default = JustEnoughMod-shell;
        packages.default = JustEnoughMod;
      });
}
