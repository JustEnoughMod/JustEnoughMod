{ dylib, ... }:
final: _: {
  JustEnoughMod = with final;
    let libPath = [ vulkan-loader ];
    in clangStdenv.mkDerivation {
      inherit libPath;

      name = "JustEnoughMod";

      src = ./.;

      enableParallelBuilding = true;

      nativeBuildInputs =
        [ clang-tools_17 pkg-config meson ninja makeWrapper doxygen graphviz ];
      buildInputs =
        [ glfw-wayland wayland spdlog vulkan-headers vulkan-validation-layers ]
        ++ libPath;

      preConfigure = ''
        cp -r ${dylib} subprojects/dylib

        chmod 777 -R subprojects
      '';

      installPhase = ''
        mkdir -p $out/bin
        mkdir -p $out/bin/Plugins
        cp JustEnoughMod $out/bin
        cp libJustEnoughMod.so $out/bin
        wrapProgram $out/bin/JustEnoughMod \
          --prefix LD_LIBRARY_PATH : ${lib.makeLibraryPath libPath}
      '';
    };
}
