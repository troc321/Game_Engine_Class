#include "engine/proto.h"

int main(int argc, char *argv[]) {
    char filename[1000];

#ifdef PROTO_PYTHON_FILENAME
    sprintf(filename, "%s", PROTO_PYTHON_FILENAME);
#else
    if (argc < 2) {
        fprintf(stderr,"Usage: %s [GAME.PY]\n", argv[0]);
        return 1;
    }
    sprintf(filename, "%s", argv[1]);
#endif

    return start_engine(filename);
}