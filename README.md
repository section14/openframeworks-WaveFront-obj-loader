Wave Front .obj File Loader
===============

This is a small parser class written in C++ to parse .obj files for use in openframeworks projects. While there are calls made to openframeworks specific functions, it could be easily re-factored to run on other openGL projects. As it stands, this class returns an ofMesh object.

This was made to be used with models exported from Blender, but should run fine with other .obj files. IMPORTANT: when exporting models from blender, make sure both "Write Normals" and "Triangulate Faces" is checked. Otherwise, it will crash, or look weird at the very least.

This script will also parse material files (.mtl) along with .obj files. Material files must be named the same as the object file (ie. model.obj / model.mtl). A simple method call toggles between the two.

```
objLoader->loadMaterial(true); //loads material file
objLoader->loadMaterial(false); //doesn't load material file
```

As it stands, this imports the model and materials only, discarding texture information. It may be a future add on, or you can feel free to fork the code.
