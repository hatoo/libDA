#include "Hand.h"
#include "Card.h"
#include <cstdint>
                      //mysuit locksuit num joker
constexpr uint8_t groupmemo[16][16][5][2][16] = {{{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},},{{{{1,0},{1,3,5,9,0},},{{1,0},{1,0},},{{0},{3,5,9,0},},{{0},{0},},{{0},{0},},},{{{1,0},{1,3,5,9,0},},{{1,0},{1,0},},{{0},{3,5,9,0},},{{0},{0},},{{0},{0},},},{{{0},{3,0},},{{0},{0},},{{0},{3,0},},{{0},{0},},{{0},{0},},},{{{0},{3,0},},{{0},{0},},{{0},{3,0},},{{0},{0},},{{0},{0},},},{{{0},{5,0},},{{0},{0},},{{0},{5,0},},{{0},{0},},{{0},{0},},},{{{0},{5,0},},{{0},{0},},{{0},{5,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{9,0},},{{0},{0},},{{0},{9,0},},{{0},{0},},{{0},{0},},},{{{0},{9,0},},{{0},{0},},{{0},{9,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},},{{{{2,0},{2,3,6,10,0},},{{2,0},{2,0},},{{0},{3,6,10,0},},{{0},{0},},{{0},{0},},},{{{0},{3,0},},{{0},{0},},{{0},{3,0},},{{0},{0},},{{0},{0},},},{{{2,0},{2,3,6,10,0},},{{2,0},{2,0},},{{0},{3,6,10,0},},{{0},{0},},{{0},{0},},},{{{0},{3,0},},{{0},{0},},{{0},{3,0},},{{0},{0},},{{0},{0},},},{{{0},{6,0},},{{0},{0},},{{0},{6,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{6,0},},{{0},{0},},{{0},{6,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{10,0},},{{0},{0},},{{0},{10,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{10,0},},{{0},{0},},{{0},{10,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},},{{{{1,2,3,0},{1,2,3,5,6,7,9,10,11,0},},{{1,2,0},{1,2,0},},{{3,0},{3,5,6,9,10,0},},{{0},{7,11,0},},{{0},{0},},},{{{1,3,0},{1,3,5,7,9,11,0},},{{1,0},{1,0},},{{3,0},{3,5,9,0},},{{0},{7,11,0},},{{0},{0},},},{{{2,3,0},{2,3,6,7,10,11,0},},{{2,0},{2,0},},{{3,0},{3,6,10,0},},{{0},{7,11,0},},{{0},{0},},},{{{3,0},{3,7,11,0},},{{0},{0},},{{3,0},{3,0},},{{0},{7,11,0},},{{0},{0},},},{{{0},{5,6,7,0},},{{0},{0},},{{0},{5,6,0},},{{0},{7,0},},{{0},{0},},},{{{0},{5,7,0},},{{0},{0},},{{0},{5,0},},{{0},{7,0},},{{0},{0},},},{{{0},{6,7,0},},{{0},{0},},{{0},{6,0},},{{0},{7,0},},{{0},{0},},},{{{0},{7,0},},{{0},{0},},{{0},{0},},{{0},{7,0},},{{0},{0},},},{{{0},{9,10,11,0},},{{0},{0},},{{0},{9,10,0},},{{0},{11,0},},{{0},{0},},},{{{0},{9,11,0},},{{0},{0},},{{0},{9,0},},{{0},{11,0},},{{0},{0},},},{{{0},{10,11,0},},{{0},{0},},{{0},{10,0},},{{0},{11,0},},{{0},{0},},},{{{0},{11,0},},{{0},{0},},{{0},{0},},{{0},{11,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},},{{{{4,0},{4,5,6,12,0},},{{4,0},{4,0},},{{0},{5,6,12,0},},{{0},{0},},{{0},{0},},},{{{0},{5,0},},{{0},{0},},{{0},{5,0},},{{0},{0},},{{0},{0},},},{{{0},{6,0},},{{0},{0},},{{0},{6,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{4,0},{4,5,6,12,0},},{{4,0},{4,0},},{{0},{5,6,12,0},},{{0},{0},},{{0},{0},},},{{{0},{5,0},},{{0},{0},},{{0},{5,0},},{{0},{0},},{{0},{0},},},{{{0},{6,0},},{{0},{0},},{{0},{6,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{12,0},},{{0},{0},},{{0},{12,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{12,0},},{{0},{0},},{{0},{12,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},},{{{{1,4,5,0},{1,3,4,5,6,7,9,12,13,0},},{{1,4,0},{1,4,0},},{{5,0},{3,5,6,9,12,0},},{{0},{7,13,0},},{{0},{0},},},{{{1,5,0},{1,3,5,7,9,13,0},},{{1,0},{1,0},},{{5,0},{3,5,9,0},},{{0},{7,13,0},},{{0},{0},},},{{{0},{3,6,7,0},},{{0},{0},},{{0},{3,6,0},},{{0},{7,0},},{{0},{0},},},{{{0},{3,7,0},},{{0},{0},},{{0},{3,0},},{{0},{7,0},},{{0},{0},},},{{{4,5,0},{4,5,6,7,12,13,0},},{{4,0},{4,0},},{{5,0},{5,6,12,0},},{{0},{7,13,0},},{{0},{0},},},{{{5,0},{5,7,13,0},},{{0},{0},},{{5,0},{5,0},},{{0},{7,13,0},},{{0},{0},},},{{{0},{6,7,0},},{{0},{0},},{{0},{6,0},},{{0},{7,0},},{{0},{0},},},{{{0},{7,0},},{{0},{0},},{{0},{0},},{{0},{7,0},},{{0},{0},},},{{{0},{9,12,13,0},},{{0},{0},},{{0},{9,12,0},},{{0},{13,0},},{{0},{0},},},{{{0},{9,13,0},},{{0},{0},},{{0},{9,0},},{{0},{13,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{12,13,0},},{{0},{0},},{{0},{12,0},},{{0},{13,0},},{{0},{0},},},{{{0},{13,0},},{{0},{0},},{{0},{0},},{{0},{13,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},},{{{{2,4,6,0},{2,3,4,5,6,7,10,12,14,0},},{{2,4,0},{2,4,0},},{{6,0},{3,5,6,10,12,0},},{{0},{7,14,0},},{{0},{0},},},{{{0},{3,5,7,0},},{{0},{0},},{{0},{3,5,0},},{{0},{7,0},},{{0},{0},},},{{{2,6,0},{2,3,6,7,10,14,0},},{{2,0},{2,0},},{{6,0},{3,6,10,0},},{{0},{7,14,0},},{{0},{0},},},{{{0},{3,7,0},},{{0},{0},},{{0},{3,0},},{{0},{7,0},},{{0},{0},},},{{{4,6,0},{4,5,6,7,12,14,0},},{{4,0},{4,0},},{{6,0},{5,6,12,0},},{{0},{7,14,0},},{{0},{0},},},{{{0},{5,7,0},},{{0},{0},},{{0},{5,0},},{{0},{7,0},},{{0},{0},},},{{{6,0},{6,7,14,0},},{{0},{0},},{{6,0},{6,0},},{{0},{7,14,0},},{{0},{0},},},{{{0},{7,0},},{{0},{0},},{{0},{0},},{{0},{7,0},},{{0},{0},},},{{{0},{10,12,14,0},},{{0},{0},},{{0},{10,12,0},},{{0},{14,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{10,14,0},},{{0},{0},},{{0},{10,0},},{{0},{14,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{12,14,0},},{{0},{0},},{{0},{12,0},},{{0},{14,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{14,0},},{{0},{0},},{{0},{0},},{{0},{14,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},},{{{{1,2,3,4,5,6,7,0},{1,2,3,4,5,6,7,9,10,11,12,13,14,15,0},},{{1,2,4,0},{1,2,4,0},},{{3,5,6,0},{3,5,6,9,10,12,0},},{{7,0},{7,11,13,14,0},},{{0},{15,0},},},{{{1,3,5,7,0},{1,3,5,7,9,11,13,15,0},},{{1,0},{1,0},},{{3,5,0},{3,5,9,0},},{{7,0},{7,11,13,0},},{{0},{15,0},},},{{{2,3,6,7,0},{2,3,6,7,10,11,14,15,0},},{{2,0},{2,0},},{{3,6,0},{3,6,10,0},},{{7,0},{7,11,14,0},},{{0},{15,0},},},{{{3,7,0},{3,7,11,15,0},},{{0},{0},},{{3,0},{3,0},},{{7,0},{7,11,0},},{{0},{15,0},},},{{{4,5,6,7,0},{4,5,6,7,12,13,14,15,0},},{{4,0},{4,0},},{{5,6,0},{5,6,12,0},},{{7,0},{7,13,14,0},},{{0},{15,0},},},{{{5,7,0},{5,7,13,15,0},},{{0},{0},},{{5,0},{5,0},},{{7,0},{7,13,0},},{{0},{15,0},},},{{{6,7,0},{6,7,14,15,0},},{{0},{0},},{{6,0},{6,0},},{{7,0},{7,14,0},},{{0},{15,0},},},{{{7,0},{7,15,0},},{{0},{0},},{{0},{0},},{{7,0},{7,0},},{{0},{15,0},},},{{{0},{9,10,11,12,13,14,15,0},},{{0},{0},},{{0},{9,10,12,0},},{{0},{11,13,14,0},},{{0},{15,0},},},{{{0},{9,11,13,15,0},},{{0},{0},},{{0},{9,0},},{{0},{11,13,0},},{{0},{15,0},},},{{{0},{10,11,14,15,0},},{{0},{0},},{{0},{10,0},},{{0},{11,14,0},},{{0},{15,0},},},{{{0},{11,15,0},},{{0},{0},},{{0},{0},},{{0},{11,0},},{{0},{15,0},},},{{{0},{12,13,14,15,0},},{{0},{0},},{{0},{12,0},},{{0},{13,14,0},},{{0},{15,0},},},{{{0},{13,15,0},},{{0},{0},},{{0},{0},},{{0},{13,0},},{{0},{15,0},},},{{{0},{14,15,0},},{{0},{0},},{{0},{0},},{{0},{14,0},},{{0},{15,0},},},{{{0},{15,0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{15,0},},},},{{{{8,0},{8,9,10,12,0},},{{8,0},{8,0},},{{0},{9,10,12,0},},{{0},{0},},{{0},{0},},},{{{0},{9,0},},{{0},{0},},{{0},{9,0},},{{0},{0},},{{0},{0},},},{{{0},{10,0},},{{0},{0},},{{0},{10,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{12,0},},{{0},{0},},{{0},{12,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{8,0},{8,9,10,12,0},},{{8,0},{8,0},},{{0},{9,10,12,0},},{{0},{0},},{{0},{0},},},{{{0},{9,0},},{{0},{0},},{{0},{9,0},},{{0},{0},},{{0},{0},},},{{{0},{10,0},},{{0},{0},},{{0},{10,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{12,0},},{{0},{0},},{{0},{12,0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},},{{{{1,8,9,0},{1,3,5,8,9,10,11,12,13,0},},{{1,8,0},{1,8,0},},{{9,0},{3,5,9,10,12,0},},{{0},{11,13,0},},{{0},{0},},},{{{1,9,0},{1,3,5,9,11,13,0},},{{1,0},{1,0},},{{9,0},{3,5,9,0},},{{0},{11,13,0},},{{0},{0},},},{{{0},{3,10,11,0},},{{0},{0},},{{0},{3,10,0},},{{0},{11,0},},{{0},{0},},},{{{0},{3,11,0},},{{0},{0},},{{0},{3,0},},{{0},{11,0},},{{0},{0},},},{{{0},{5,12,13,0},},{{0},{0},},{{0},{5,12,0},},{{0},{13,0},},{{0},{0},},},{{{0},{5,13,0},},{{0},{0},},{{0},{5,0},},{{0},{13,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{8,9,0},{8,9,10,11,12,13,0},},{{8,0},{8,0},},{{9,0},{9,10,12,0},},{{0},{11,13,0},},{{0},{0},},},{{{9,0},{9,11,13,0},},{{0},{0},},{{9,0},{9,0},},{{0},{11,13,0},},{{0},{0},},},{{{0},{10,11,0},},{{0},{0},},{{0},{10,0},},{{0},{11,0},},{{0},{0},},},{{{0},{11,0},},{{0},{0},},{{0},{0},},{{0},{11,0},},{{0},{0},},},{{{0},{12,13,0},},{{0},{0},},{{0},{12,0},},{{0},{13,0},},{{0},{0},},},{{{0},{13,0},},{{0},{0},},{{0},{0},},{{0},{13,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},},{{{{2,8,10,0},{2,3,6,8,9,10,11,12,14,0},},{{2,8,0},{2,8,0},},{{10,0},{3,6,9,10,12,0},},{{0},{11,14,0},},{{0},{0},},},{{{0},{3,9,11,0},},{{0},{0},},{{0},{3,9,0},},{{0},{11,0},},{{0},{0},},},{{{2,10,0},{2,3,6,10,11,14,0},},{{2,0},{2,0},},{{10,0},{3,6,10,0},},{{0},{11,14,0},},{{0},{0},},},{{{0},{3,11,0},},{{0},{0},},{{0},{3,0},},{{0},{11,0},},{{0},{0},},},{{{0},{6,12,14,0},},{{0},{0},},{{0},{6,12,0},},{{0},{14,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{6,14,0},},{{0},{0},},{{0},{6,0},},{{0},{14,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{8,10,0},{8,9,10,11,12,14,0},},{{8,0},{8,0},},{{10,0},{9,10,12,0},},{{0},{11,14,0},},{{0},{0},},},{{{0},{9,11,0},},{{0},{0},},{{0},{9,0},},{{0},{11,0},},{{0},{0},},},{{{10,0},{10,11,14,0},},{{0},{0},},{{10,0},{10,0},},{{0},{11,14,0},},{{0},{0},},},{{{0},{11,0},},{{0},{0},},{{0},{0},},{{0},{11,0},},{{0},{0},},},{{{0},{12,14,0},},{{0},{0},},{{0},{12,0},},{{0},{14,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{0},{14,0},},{{0},{0},},{{0},{0},},{{0},{14,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},},{{{{1,2,3,8,9,10,11,0},{1,2,3,5,6,7,8,9,10,11,12,13,14,15,0},},{{1,2,8,0},{1,2,8,0},},{{3,9,10,0},{3,5,6,9,10,12,0},},{{11,0},{7,11,13,14,0},},{{0},{15,0},},},{{{1,3,9,11,0},{1,3,5,7,9,11,13,15,0},},{{1,0},{1,0},},{{3,9,0},{3,5,9,0},},{{11,0},{7,11,13,0},},{{0},{15,0},},},{{{2,3,10,11,0},{2,3,6,7,10,11,14,15,0},},{{2,0},{2,0},},{{3,10,0},{3,6,10,0},},{{11,0},{7,11,14,0},},{{0},{15,0},},},{{{3,11,0},{3,7,11,15,0},},{{0},{0},},{{3,0},{3,0},},{{11,0},{7,11,0},},{{0},{15,0},},},{{{0},{5,6,7,12,13,14,15,0},},{{0},{0},},{{0},{5,6,12,0},},{{0},{7,13,14,0},},{{0},{15,0},},},{{{0},{5,7,13,15,0},},{{0},{0},},{{0},{5,0},},{{0},{7,13,0},},{{0},{15,0},},},{{{0},{6,7,14,15,0},},{{0},{0},},{{0},{6,0},},{{0},{7,14,0},},{{0},{15,0},},},{{{0},{7,15,0},},{{0},{0},},{{0},{0},},{{0},{7,0},},{{0},{15,0},},},{{{8,9,10,11,0},{8,9,10,11,12,13,14,15,0},},{{8,0},{8,0},},{{9,10,0},{9,10,12,0},},{{11,0},{11,13,14,0},},{{0},{15,0},},},{{{9,11,0},{9,11,13,15,0},},{{0},{0},},{{9,0},{9,0},},{{11,0},{11,13,0},},{{0},{15,0},},},{{{10,11,0},{10,11,14,15,0},},{{0},{0},},{{10,0},{10,0},},{{11,0},{11,14,0},},{{0},{15,0},},},{{{11,0},{11,15,0},},{{0},{0},},{{0},{0},},{{11,0},{11,0},},{{0},{15,0},},},{{{0},{12,13,14,15,0},},{{0},{0},},{{0},{12,0},},{{0},{13,14,0},},{{0},{15,0},},},{{{0},{13,15,0},},{{0},{0},},{{0},{0},},{{0},{13,0},},{{0},{15,0},},},{{{0},{14,15,0},},{{0},{0},},{{0},{0},},{{0},{14,0},},{{0},{15,0},},},{{{0},{15,0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{15,0},},},},{{{{4,8,12,0},{4,5,6,8,9,10,12,13,14,0},},{{4,8,0},{4,8,0},},{{12,0},{5,6,9,10,12,0},},{{0},{13,14,0},},{{0},{0},},},{{{0},{5,9,13,0},},{{0},{0},},{{0},{5,9,0},},{{0},{13,0},},{{0},{0},},},{{{0},{6,10,14,0},},{{0},{0},},{{0},{6,10,0},},{{0},{14,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{4,12,0},{4,5,6,12,13,14,0},},{{4,0},{4,0},},{{12,0},{5,6,12,0},},{{0},{13,14,0},},{{0},{0},},},{{{0},{5,13,0},},{{0},{0},},{{0},{5,0},},{{0},{13,0},},{{0},{0},},},{{{0},{6,14,0},},{{0},{0},},{{0},{6,0},},{{0},{14,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{8,12,0},{8,9,10,12,13,14,0},},{{8,0},{8,0},},{{12,0},{9,10,12,0},},{{0},{13,14,0},},{{0},{0},},},{{{0},{9,13,0},},{{0},{0},},{{0},{9,0},},{{0},{13,0},},{{0},{0},},},{{{0},{10,14,0},},{{0},{0},},{{0},{10,0},},{{0},{14,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},{{{12,0},{12,13,14,0},},{{0},{0},},{{12,0},{12,0},},{{0},{13,14,0},},{{0},{0},},},{{{0},{13,0},},{{0},{0},},{{0},{0},},{{0},{13,0},},{{0},{0},},},{{{0},{14,0},},{{0},{0},},{{0},{0},},{{0},{14,0},},{{0},{0},},},{{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{0},},},},{{{{1,4,5,8,9,12,13,0},{1,3,4,5,6,7,8,9,10,11,12,13,14,15,0},},{{1,4,8,0},{1,4,8,0},},{{5,9,12,0},{3,5,6,9,10,12,0},},{{13,0},{7,11,13,14,0},},{{0},{15,0},},},{{{1,5,9,13,0},{1,3,5,7,9,11,13,15,0},},{{1,0},{1,0},},{{5,9,0},{3,5,9,0},},{{13,0},{7,11,13,0},},{{0},{15,0},},},{{{0},{3,6,7,10,11,14,15,0},},{{0},{0},},{{0},{3,6,10,0},},{{0},{7,11,14,0},},{{0},{15,0},},},{{{0},{3,7,11,15,0},},{{0},{0},},{{0},{3,0},},{{0},{7,11,0},},{{0},{15,0},},},{{{4,5,12,13,0},{4,5,6,7,12,13,14,15,0},},{{4,0},{4,0},},{{5,12,0},{5,6,12,0},},{{13,0},{7,13,14,0},},{{0},{15,0},},},{{{5,13,0},{5,7,13,15,0},},{{0},{0},},{{5,0},{5,0},},{{13,0},{7,13,0},},{{0},{15,0},},},{{{0},{6,7,14,15,0},},{{0},{0},},{{0},{6,0},},{{0},{7,14,0},},{{0},{15,0},},},{{{0},{7,15,0},},{{0},{0},},{{0},{0},},{{0},{7,0},},{{0},{15,0},},},{{{8,9,12,13,0},{8,9,10,11,12,13,14,15,0},},{{8,0},{8,0},},{{9,12,0},{9,10,12,0},},{{13,0},{11,13,14,0},},{{0},{15,0},},},{{{9,13,0},{9,11,13,15,0},},{{0},{0},},{{9,0},{9,0},},{{13,0},{11,13,0},},{{0},{15,0},},},{{{0},{10,11,14,15,0},},{{0},{0},},{{0},{10,0},},{{0},{11,14,0},},{{0},{15,0},},},{{{0},{11,15,0},},{{0},{0},},{{0},{0},},{{0},{11,0},},{{0},{15,0},},},{{{12,13,0},{12,13,14,15,0},},{{0},{0},},{{12,0},{12,0},},{{13,0},{13,14,0},},{{0},{15,0},},},{{{13,0},{13,15,0},},{{0},{0},},{{0},{0},},{{13,0},{13,0},},{{0},{15,0},},},{{{0},{14,15,0},},{{0},{0},},{{0},{0},},{{0},{14,0},},{{0},{15,0},},},{{{0},{15,0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{15,0},},},},{{{{2,4,6,8,10,12,14,0},{2,3,4,5,6,7,8,9,10,11,12,13,14,15,0},},{{2,4,8,0},{2,4,8,0},},{{6,10,12,0},{3,5,6,9,10,12,0},},{{14,0},{7,11,13,14,0},},{{0},{15,0},},},{{{0},{3,5,7,9,11,13,15,0},},{{0},{0},},{{0},{3,5,9,0},},{{0},{7,11,13,0},},{{0},{15,0},},},{{{2,6,10,14,0},{2,3,6,7,10,11,14,15,0},},{{2,0},{2,0},},{{6,10,0},{3,6,10,0},},{{14,0},{7,11,14,0},},{{0},{15,0},},},{{{0},{3,7,11,15,0},},{{0},{0},},{{0},{3,0},},{{0},{7,11,0},},{{0},{15,0},},},{{{4,6,12,14,0},{4,5,6,7,12,13,14,15,0},},{{4,0},{4,0},},{{6,12,0},{5,6,12,0},},{{14,0},{7,13,14,0},},{{0},{15,0},},},{{{0},{5,7,13,15,0},},{{0},{0},},{{0},{5,0},},{{0},{7,13,0},},{{0},{15,0},},},{{{6,14,0},{6,7,14,15,0},},{{0},{0},},{{6,0},{6,0},},{{14,0},{7,14,0},},{{0},{15,0},},},{{{0},{7,15,0},},{{0},{0},},{{0},{0},},{{0},{7,0},},{{0},{15,0},},},{{{8,10,12,14,0},{8,9,10,11,12,13,14,15,0},},{{8,0},{8,0},},{{10,12,0},{9,10,12,0},},{{14,0},{11,13,14,0},},{{0},{15,0},},},{{{0},{9,11,13,15,0},},{{0},{0},},{{0},{9,0},},{{0},{11,13,0},},{{0},{15,0},},},{{{10,14,0},{10,11,14,15,0},},{{0},{0},},{{10,0},{10,0},},{{14,0},{11,14,0},},{{0},{15,0},},},{{{0},{11,15,0},},{{0},{0},},{{0},{0},},{{0},{11,0},},{{0},{15,0},},},{{{12,14,0},{12,13,14,15,0},},{{0},{0},},{{12,0},{12,0},},{{14,0},{13,14,0},},{{0},{15,0},},},{{{0},{13,15,0},},{{0},{0},},{{0},{0},},{{0},{13,0},},{{0},{15,0},},},{{{14,0},{14,15,0},},{{0},{0},},{{0},{0},},{{14,0},{14,0},},{{0},{15,0},},},{{{0},{15,0},},{{0},{0},},{{0},{0},},{{0},{0},},{{0},{15,0},},},},{{{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0},{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0},},{{1,2,4,8,0},{1,2,4,8,0},},{{3,5,6,9,10,12,0},{3,5,6,9,10,12,0},},{{7,11,13,14,0},{7,11,13,14,0},},{{15,0},{15,0},},},{{{1,3,5,7,9,11,13,15,0},{1,3,5,7,9,11,13,15,0},},{{1,0},{1,0},},{{3,5,9,0},{3,5,9,0},},{{7,11,13,0},{7,11,13,0},},{{15,0},{15,0},},},{{{2,3,6,7,10,11,14,15,0},{2,3,6,7,10,11,14,15,0},},{{2,0},{2,0},},{{3,6,10,0},{3,6,10,0},},{{7,11,14,0},{7,11,14,0},},{{15,0},{15,0},},},{{{3,7,11,15,0},{3,7,11,15,0},},{{0},{0},},{{3,0},{3,0},},{{7,11,0},{7,11,0},},{{15,0},{15,0},},},{{{4,5,6,7,12,13,14,15,0},{4,5,6,7,12,13,14,15,0},},{{4,0},{4,0},},{{5,6,12,0},{5,6,12,0},},{{7,13,14,0},{7,13,14,0},},{{15,0},{15,0},},},{{{5,7,13,15,0},{5,7,13,15,0},},{{0},{0},},{{5,0},{5,0},},{{7,13,0},{7,13,0},},{{15,0},{15,0},},},{{{6,7,14,15,0},{6,7,14,15,0},},{{0},{0},},{{6,0},{6,0},},{{7,14,0},{7,14,0},},{{15,0},{15,0},},},{{{7,15,0},{7,15,0},},{{0},{0},},{{0},{0},},{{7,0},{7,0},},{{15,0},{15,0},},},{{{8,9,10,11,12,13,14,15,0},{8,9,10,11,12,13,14,15,0},},{{8,0},{8,0},},{{9,10,12,0},{9,10,12,0},},{{11,13,14,0},{11,13,14,0},},{{15,0},{15,0},},},{{{9,11,13,15,0},{9,11,13,15,0},},{{0},{0},},{{9,0},{9,0},},{{11,13,0},{11,13,0},},{{15,0},{15,0},},},{{{10,11,14,15,0},{10,11,14,15,0},},{{0},{0},},{{10,0},{10,0},},{{11,14,0},{11,14,0},},{{15,0},{15,0},},},{{{11,15,0},{11,15,0},},{{0},{0},},{{0},{0},},{{11,0},{11,0},},{{15,0},{15,0},},},{{{12,13,14,15,0},{12,13,14,15,0},},{{0},{0},},{{12,0},{12,0},},{{13,14,0},{13,14,0},},{{15,0},{15,0},},},{{{13,15,0},{13,15,0},},{{0},{0},},{{0},{0},},{{13,0},{13,0},},{{15,0},{15,0},},},{{{14,15,0},{14,15,0},},{{0},{0},},{{0},{0},},{{14,0},{14,0},},{{15,0},{15,0},},},{{{15,0},{15,0},},{{0},{0},},{{0},{0},},{{0},{0},},{{15,0},{15,0},},},},};

int DA::getGroup(Cards tefuda,Hand *out){
	Hand *ptr = out;
	int hasjoker = tefuda&JOKER?1:0;
	for(int i=1;i<14;i++){
		const uint8_t suit = (tefuda>>(4*i))&0xf;
		uint8_t *p = (uint8_t*)groupmemo[suit][0][0][hasjoker];
		while(*p){
			*ptr++ = DA::Hand::Group(*p,i,(*p)^(suit&(*p)));
			p++;
		}
	}
	if(hasjoker){
		*ptr++ = DA::SingleJoker;
	}
	return ptr-out;
}

int DA::getGroup(Cards tefuda,const Hand &group,bool lock,bool rev,Hand *out){
	Hand *ptr = out;
	const int hasjoker = tefuda&JOKER?1:0;
	int qty = group.qty();
	if(qty==1 && hasjoker){
		*ptr++ = SingleJoker;
	}
	if((tefuda&S3)&&qty==1&&(group.joker!=0)){
		*ptr = Hand::Group(1,1);
		return 1;
	}
	uint8_t lsuit = lock?group.suit:0;
	const int start = rev?1:group.low+1;
	const int end = rev?group.low:14;
	for(int i=start;i<end;i++){
		const uint8_t suit = (tefuda>>(4*i))&0xf;
		uint8_t *p = (uint8_t*)groupmemo[suit][lsuit][qty][hasjoker];
		while(*p){
			*ptr++ = DA::Hand::Group(*p,i,(*p)^(suit&(*p)));
			p++;
		}
	}

	return ptr-out;
}

int DA::getStair(Cards tefuda,Hand *out){
	Hand *ptr = out;
	const bool hasjoker = (tefuda&JOKER)!=0;
	//tefuda &= ~JOKER;
	for(int low=1;low<14;low++){
		for(int i=0;i<4;i++){
			const Cards suit = u<<i;
			bool jused = !hasjoker;
			uint8_t jord = DA::Hand::nojokerord;
			for(int high = low;high<14;high++){
				if(((tefuda>>(4*high))&suit)==0){
					if(!jused){
						jused = true;
						jord = high;
					}else{
						break;
					}
				}
				const int len = high-low+1;
				if(len>=3){
					*ptr++ = DA::Hand::Stair(suit,low,high,jord);
				}
			}
		}
	}
	return ptr-out;
}

int DA::getStair(Cards tefuda,const Hand &stair,bool lock,bool rev,Hand *out){
	Hand *ptr = out;
	const bool hasjoker = (tefuda&JOKER)!=0;
	tefuda &= ~JOKER;
	const int qty = stair.qty();
	const int start = rev?0:stair.high+1;
	const int end = rev?stair.low:15;

	const uint8_t suits[] = {0x1,0x2,0x4,0x8,stair.suit};
	const int ss = lock?4:0;
	const int se = lock?5:4;
	for(int low=start;low<end;low++){
		for(int i=ss;i<se;i++){
			const Cards suit = suits[i];//u<<i;
			bool jused = !hasjoker;
			uint8_t jord = DA::Hand::nojokerord;
			for(int high = low;high<end;high++){
				if(((tefuda>>(4*high))&suit)==0){
					if(!jused){
						jused = true;
						jord = high;
					}else{
						break;
					}
				}
				const int len = high-low+1;
				if(len==qty){
					*ptr++ = DA::Hand::Stair(suit,low,high,jord);
					break;
				}
			}
		}
	}
	return ptr-out;
}

int DA::validHands(Cards tefuda,Hand *out){
	Hand *ptr = out;
	ptr+=DA::getGroup(tefuda,ptr);
	ptr+=DA::getStair(tefuda,ptr);
	return ptr-out;
}

int DA::validHands(Cards tefuda,const Hand &hand,bool lock,bool rev,Hand *out){
	int n=0;
	switch(hand.type){
		case HandType::PASS:
		return validHands(tefuda,out);
		case HandType::GROUP:
			n = getGroup(tefuda,hand,lock,rev,out);
			break;
		case HandType::STAIR:
			n = getStair(tefuda,hand,lock,rev,out);
			break;
	}
	out[n]=PassHand;
	return n+1;
}

bool DA::Hand::operator==(const Hand &h)const{
	return type==h.type&&low==h.low&&high==h.high&&joker==h.joker;
}

uint64_t DA::Hand::toBin()const{
	const uint64_t t64 = (uint64_t)type;
	const uint64_t s64 = suit;
	const uint64_t l64 = low;
	const uint64_t h64 = high;
	const uint64_t j64 = joker;
	return t64|(s64<<8)|(l64<<16)|(h64<<24)|(j64<<32);
}
DA::Hand DA::Hand::fromBin(uint64_t bin){
	HandType type = (HandType)(bin&0xf);
	uint8_t suit  = (bin>>8)&0xff;
	uint8_t low   = (bin>>16)&0xff;
	uint8_t high  = (bin>>24)&0xff;
	uint8_t joker = (bin>>32)&0xff;
	return Hand(type,suit,low,high,joker);
}