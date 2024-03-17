{
  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    pre-commit-hooks.url = "github:cachix/pre-commit-hooks.nix";
    dylib = {
      url = "https://github.com/JustEnoughMod/dylib.meson";
      flake = false;
    };
  };

  outputs = { self, nixpkgs, pre-commit-hooks, dylib }:
    let
      supportedSystems =
        [ "x86_64-linux" "x86_64-darwin" "aarch64-linux" "aarch64-darwin" ];

      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;

      pkgs = forAllSystems (system:
        import nixpkgs {
          inherit system;
          overlays = [ self.overlays.${system}.default ];
        });

    in {
      overlays = forAllSystems
        (_: { default = import ./overlay.nix { inherit dylib; }; });

      devShells = forAllSystems (system: {
        precommit = pkgs.${system}.mkShell {
          inherit (self.checks.${system}.pre-commit-check) shellHook;
        };

        default = pkgs.${system}.mkShell {
          inherit (self.checks.${system}.pre-commit-check) shellHook;

          inherit (pkgs.${system}.JustEnoughMod) nativeBuildInputs buildInputs;

          LD_LIBRARY_PATH = pkgs.${system}.lib.makeLibraryPath
            pkgs.${system}.JustEnoughMod.libPath;
        };
      });

      packages =
        forAllSystems (system: { default = pkgs.${system}.JustEnoughMod; });

      checks = forAllSystems (system: {
        pre-commit-check = pre-commit-hooks.lib.${system}.run {
          src = ./.;
          hooks = {
            check-added-large-files = {
              enable = true;
              name = "check-added-large-files";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/check-added-large-files";
            };
            check-case-conflicts = {
              enable = true;
              name = "check-case-conflicts";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/check-case-conflict";
              types = [ "file" ];
            };
            check-executables-have-shebangs = {
              enable = true;
              name = "check-executables-have-shebangs";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/check-executables-have-shebangs";
              types = [ "text" "executable" ];
            };
            check-json = {
              enable = true;
              name = "check-json";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/check-json";
              types = [ "json" ];
            };
            check-merge-conflicts = {
              enable = true;
              name = "check-merge-conflicts";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/check-merge-conflict";
              types = [ "text" ];
            };
            check-shebang-scripts-are-executable = {
              enable = true;
              name = "check-shebang-scripts-are-executable";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/check-shebang-scripts-are-executable";
              types = [ "text" ];
            };
            check-symlinks = {
              enable = true;
              name = "check-symlinks";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/check-symlinks";
              types = [ "symlink" ];
            };
            check-toml = {
              enable = true;
              name = "check-toml";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/check-toml";
              types = [ "toml" ];
            };
            check-xml = {
              enable = true;
              name = "check-xml";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/check-xml";
              types = [ "xml" ];
            };
            check-yaml = {
              enable = true;
              name = "check-yaml";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/check-yaml --multi";
              types = [ "yaml" ];
            };
            detect-private-keys = {
              enable = true;
              name = "detect-private-keys";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/detect-private-key";
              types = [ "text" ];
            };
            destroyed-symlinks = {
              enable = true;
              name = "destroyed-symlinks";
              description = "Detect the presence of private keys.";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/destroyed-symlinks";
              types = [ "text" ];
            };
            end-of-file-fixer = {
              enable = true;
              name = "end-of-file-fixer";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/end-of-file-fixer";
              types = [ "text" ];
            };
            fix-byte-order-marker = {
              enable = true;
              name = "fix-byte-order-marker";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/fix-byte-order-marker";
              types = [ "text" ];
            };
            mixed-line-endings = {
              enable = true;
              name = "mixed-line-endings";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/mixed-line-ending";
              types = [ "text" ];
            };
            pretty-format-json = {
              enable = true;
              name = "pretty-format-json";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/pretty-format-json --autofix";
              types = [ "json" ];
            };
            sort-simple-yaml = {
              enable = true;
              name = "sort-simple-yaml";
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/sort-simple-yaml";
              files = "(\\.yaml$)|(\\.yml$)";
            };
            trim-trailing-whitespace = {
              enable = true;
              name = "trim-trailing-whitespace";
              types = [ "text" ];
              entry = "${
                  pkgs.${system}.python3Packages.pre-commit-hooks
                }/bin/trailing-whitespace-fixer";
            };

            deadnix.enable = true;
            nil.enable = true;
            nixfmt.enable = true;
            statix.enable = true;

            shfmt.enable = true;

            clang-format = {
              enable = true;
              types_or = pkgs.${system}.lib.mkForce [ "c" "c++" ];
            };

            cppcheck = {
              enable = true;
              name = "cppcheck";
              types_or = [ "c" "c++" "objective-c" ];
              entry = "${
                  pkgs.${system}.cppcheck
                }/bin/cppcheck -q --error-exitcode=1 --error-exitcode=1 --suppress=unmatchedSuppression --suppress=missingIncludeSystem --suppress=unusedFunction";
            };
          };
        };
      });
    };
}
