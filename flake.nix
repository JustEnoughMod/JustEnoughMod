{
  inputs = { nixpkgs.url = "nixpkgs/nixos-unstable"; };

  outputs = { self, nixpkgs }:
    let
      lastModifiedDate =
        self.lastModifiedDate or self.lastModified or "19700101";
      version = builtins.substring 0 8 lastModifiedDate;

      supportedSystems = [ "x86_64-linux" "aarch64-linux" ];

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
              url = "https://github.com/LDprg/bgfx.meson";
              sha256 = "sha256-1xGy+Rja9YNUWAc70ckc5H6tEmLeSPCUJ8T//eWKE1s=";
              fetchSubmodules = true;
            };
            dylib = prev.fetchgit {
              url = "https://github.com/LDprg/dylib.meson";
              sha256 = "sha256-bdYkfmxzv30+EQ4hXmIZ07rsyjz9YtSGEIOzUBDPJpM=";
              fetchSubmodules = true;
            };
          in stdenv.mkDerivation rec {
            pname = "JustEnoughMod";
            inherit version;

            src = ./.;

            enableParallelBuilding = true;

            nativeBuildInputs =
              [ pkg-config meson ninja ccache git binutils makeWrapper ];
            buildInputs = [ SDL2 cmake libGL ];

            preConfigure = ''
              cp -r ${bgfx} subprojects/bgfx
              cp -r ${dylib} subprojects/dylib

              chmod 777 -R subprojects
            '';

            installPhase = ''
              mkdir -p $out/bin
              mv JustEnoughMod $out/bin
              mv libJustEnoughMod.so $out/bin
              wrapProgram $out/bin/JustEnoughMod \
                --prefix LD_LIBRARY_PATH : ${lib.makeLibraryPath [ libGL ]}
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
