#include "Graphics/XFTColors.h"

std::unordered_map<int, unsigned int> Graphics::XFTColors::colorMap{};
Colormap Graphics::XFTColors::cmap{};
Display* Graphics::XFTColors::display = nullptr;
Visual* Graphics::XFTColors::visual = nullptr;
std::vector<XftColor> Graphics::XFTColors::colors{};

const std::vector<XRenderColor> Graphics::XFTColors::renderColors {{{35 * 257, 38 * 257, 39 * 257, 0xffff},
                                                      {237 * 257, 21 * 257, 21 * 257, 0xffff},
                                                      {17 * 257, 209 * 257, 22 * 257, 0xffff},
                                                      {246 * 257, 116 * 257, 0 * 257, 0xffff},
                                                      {29 * 257, 153 * 257, 243 * 257, 0xffff},
                                                      {155 * 257, 89 * 257, 182 * 257, 0xffff},
                                                      {26 * 257, 188 * 257, 156 * 257, 0xffff},
                                                      {252 * 257, 252 * 257, 252 * 257, 0xffff},
                                                      {127 * 257, 140 * 257, 141 * 257, 0xffff},
                                                      {192 * 257, 57 * 257, 43 * 257, 0xffff},
                                                      {28 * 257, 220 * 257, 154 * 257, 0xffff},
                                                      {253 * 257, 188 * 257, 75 * 257, 0xffff},
                                                      {61 * 257, 174 * 257, 233 * 257, 0xffff},
                                                      {142 * 257, 68 * 257, 173 * 257, 0xffff},
                                                      {22 * 257, 160 * 257, 133 * 257, 0xffff},
                                                      {255 * 257, 255 * 257, 255 * 257, 0xffff}}};
