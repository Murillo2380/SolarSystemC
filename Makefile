space: space.c spacedef.c spacedef.h cameradef.c cameradef.h texture.c texture.h
	gcc -o space space.c spacedef.c cameradef.c texture.c -lGL -lGLU -lglut -lm -g
	@echo compilado
