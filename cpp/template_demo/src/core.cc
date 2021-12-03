/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/12/2 22:48
*/
#include "core.h"

Lane::~Lane() = default;

Lane::Lane() {
    std::cout << "Lane construction" << std::endl;
}
void Lane::get() {
    std::cout << "Lane get" << std::endl;
}

Section::~Section() = default;

Section::Section() {
    std::cout << "Section construction" << std::endl;
}


