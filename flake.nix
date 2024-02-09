{
  description = "An over-engineered Hello World in C";

  outputs = { self, nixpkgs }:
    let
      lastModifiedDate =
        self.lastModifiedDate or self.lastModified or "19700101";
      version = builtins.substring 0 8 lastModifiedDate;

      supportedSystems =
        [ "x86_64-linux" "x86_64-darwin" "aarch64-linux" "aarch64-darwin" ];

      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;

      nixpkgsFor = forAllSystems (system:
        import nixpkgs {
          inherit system;
          overlays = [ self.overlay ];
        });
    in {
      overlay = final: prev: {

        JustEnoughMod = with final;
          let
            bgfx = prev.fetchgit {
              url = "https://github.com/bkaradzic/bgfx.cmake";
              rev = "011e8efe231d3d9aba9caf634dbc86d85263d20e";
              sha256 = "sha256-whNLa8ZCgfLXwnXnp4EczNWfMqvlO71eQnagpmW7p+c=";
              fetchSubmodules = true;
            };
            sdl = prev.fetchgit {
              url = "https://github.com/libsdl-org/SDL";
              rev = "1143bdc35130e68c90c9b1a3a2069399b7f6143a";
              sha256 = "sha256-whNLa8ZCgfLXwnXnp4EczNWfMqvlO71eQnagpmW7p+c=";
              fetchSubmodules = true;
            };
          in stdenv.mkDerivation rec {
            pname = "JustEnoughMod";
            inherit version;

            src = ./.;

            enableParallelBuilding = true;

            nativeBuildInputs = [ pkg-config cmake ninja git ];
            buildInputs = [ xorg.libX11 xorg.libXrandr libGL SDL2 spirv-tools ];

            preConfigure = ''
              cp -r ${bgfx} vendor/bgfx
              cp -r ${sdl} vendor/sdl
              chmod 777 -R vendor/bgfx
              chmod 777 -R vendor/sdl
            '';

            installPhase = ''
              mkdir -p $out/bin
              mv ${pname} $out/bin
            '';
          };

      };

      packages = forAllSystems
        (system: { inherit (nixpkgsFor.${system}) JustEnoughMod; });

      defaultPackage =
        forAllSystems (system: self.packages.${system}.JustEnoughMod);

      nixosModules.JustEnoughMod = { pkgs, ... }: {
        nixpkgs.overlays = [ self.overlay ];

        environment.systemPackages = [ pkgs.JustEnoughMod ];
      };
    };
}
