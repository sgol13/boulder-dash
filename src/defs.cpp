#include "boulder-dash2/defs.hpp"

/* Lists of indispensable resources (game does not load if one of them is missing) */
const char *GRAPHIC_RESOURCES_LIST[] = {"boulder.png", "ground.png", "exit.png",
                                        "wall.png"};

const char *FONT_RESOURCES_LIST[] = {"font.ttf"};

const char *LEVEL_RESOURCES_LIST[] = {"level1"};

// automatically calculate reosources lists' sizes
const int GRAPHIC_RESOURCES_NUM = sizeof(GRAPHIC_RESOURCES_LIST) / sizeof(char *);
const int FONT_RESOURCES_NUM = sizeof(FONT_RESOURCES_LIST) / sizeof(char *);
const int LEVEL_RESOURCES_NUM = sizeof(LEVEL_RESOURCES_LIST) / sizeof(char *);