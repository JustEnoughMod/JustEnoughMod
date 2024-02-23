{ nixpkgs, bgfx, dylib, ... }:
final: prev: {
  JustEnoughMod = with final;
    clangStdenv.mkDerivation rec {
      name = "JustEnoughMod";

      src = ./.;

      enableParallelBuilding = true;

      nativeBuildInputs = [ pkg-config meson ninja ccache makeWrapper ];
      buildInputs = [ SDL2 spdlog libGL ];

      preConfigure = ''
        cp -r ${bgfx} subprojects/bgfx
        cp -r ${dylib} subprojects/dylib

        chmod 777 -R subprojects
      '';

      installPhase = ''
        mkdir -p $out/bin
        mkdir -p $out/bin/Plugins
        cp JustEnoughMod $out/bin
        cp libJustEnoughMod.so $out/bin
        wrapProgram $out/bin/JustEnoughMod \
          --prefix LD_LIBRARY_PATH : ${lib.makeLibraryPath [ libGL ]}
      '';
    };
}
