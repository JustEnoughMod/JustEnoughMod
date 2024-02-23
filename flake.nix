{
  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
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

  outputs = { self, nixpkgs, flake-utils, bgfx, dylib }:
    let overlay = import ./overlay.nix { inherit nixpkgs bgfx dylib; };
    in flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [ overlay ];
        };
      in {
        legacyPackages = rec { JustEnoughMod = pkgs.JustEnoughMod; };
        packages = nixpkgs.lib.filterAttrs (_: v: nixpkgs.lib.isDerivation v)
          self.legacyPackages.${system};
        defaultPackage = self.packages.${system}.JustEnoughMod;
      });
}
