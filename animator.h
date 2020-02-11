//
// Created by Allen on 2/5/2020.
//

#ifndef EE319K_FINAL_PROJECT_INITIAL_TESTING_ANIMATOR_H
#define EE319K_FINAL_PROJECT_INITIAL_TESTING_ANIMATOR_H

#include <cstdint>

extern void animator_animate(uint8_t animation_charIndex, uint8_t animation_animationIndex,
                    uint8_t x, uint16_t y, uint8_t frame, uint8_t persistent);

extern void animator_readCharacterSDCard(uint8_t charIndex);

#endif //EE319K_FINAL_PROJECT_INITIAL_TESTING_ANIMATOR_H
