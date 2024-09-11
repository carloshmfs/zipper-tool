#include "ProgressBar.h"

#include <iostream>

void ProgressBar::update(float percentage)
{
    m_percentage = percentage;
}

void ProgressBar::show() const
{
    for (int i = 0; i <= m_width; ++i) {
        std::cout << "\r[";

        int current_width = widthFromPercentage();
        for (int j = 0; j < m_width; ++j) {
            if (j < current_width) {
                std::cout << "=";
                continue;
            }

            if (j == current_width) {
                std::cout << ">";
                continue;
            }

            std::cout << " ";
        }

        std::cout << "] " << m_percentage << "% " << std::flush;
    }
}

int ProgressBar::widthFromPercentage() const
{
    return (m_width * m_percentage) / 100;
}

