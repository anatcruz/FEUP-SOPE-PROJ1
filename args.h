struct Args {
    unsigned int all; //-a, -all
    unsigned int bytes; //-b, --bytes
    unsigned int blockSize; //-B, --block-size=SIZE ; default SIZE=1024
    unsigned int countLinks; //-l, --count-links
    unsigned int dereference; //-L, --dereference
    unsigned int separeteDirs; //-S, --separate-dirs
    int maxDepth; //--max-depth=N ; N(0,1,...)
    char path[256]; //Dir path
};

int get_args(int argc, char *argv[]);
