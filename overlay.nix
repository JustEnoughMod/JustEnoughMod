{ bgfx, dylib, ... }:
final: _: {
  JustEnoughMod = with final;
    clangStdenv.mkDerivation {
      name = "JustEnoughMod";

      src = ./.;

      enableParallelBuilding = true;

      nativeBuildInputs = [ clang-tools pkg-config meson ninja makeWrapper ];
      buildInputs = [ SDL2 spdlog libGL vulkan-loader wayland ];

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
          --prefix LD_LIBRARY_PATH : ${
            lib.makeLibraryPath [ libGL vulkan-loader ]
          }
      '';
    };
}
