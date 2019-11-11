# CSC3223Coursework1
My drop in files for CSC3223: Graphics for Games Coursework 1

Not runnable on their own. Requires Newcastle University's OpenGL games framework. https://research.ncl.ac.uk/game/

Coursework1.cpp contains main().

Coursework Spec was as follows:
This coursework builds on the skills you have learned in graphics programming, to render a scene that demonstrates various graphical primitives and rasterisation techniques.

The challenge is to use C++ to build a renderer with OpenGL and utilise it to draw a space scene consisting of triangles, lines and points. The specification is deliberately open-ended. The scene may include a star-field, a planet surface, space debris, and/or basic space ships. Examples of old games which may be used as inspiration are the Atari arcade games Asteroids and Tempest. 

You will not lose marks for using code from the tutorials, although further marks will be gained for introducing more complex elements. Effort should be taken to implement any such features as part of a unified graphics pipeline. You will also not lose marks for basing the scene on outside sources. Remember that all such external material must be referenced and attributed properly.

The coursework should consist of four types of element:

    Primitives:
        A star-field, or night sky, consisting of point primitives.
        A spaceship or similar consisting of triangle primitives.
        A planet or asteroid or similar consisting of triangle strips or fans.
    Movement and perspective:
        Movement of some scene elements (translation).
        A three dimensional perspective view.
        Independent three dimensional rotation of scene elements.
    Colouring:
        Interpolated colour
        Textured primitives.
    Rasterisation::
        IThe depth buffer should be able to be toggled with the F1 key, with the F2, F3, and F4 showing three effective demonstrations of different depth test modes
        The alpha blending state should be able to be toggled with the F5 key, with the F6, F7 and F8 keys showing three effective demonstrations of different alpha blending modes.
