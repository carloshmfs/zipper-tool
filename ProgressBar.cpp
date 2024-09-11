#include "ProgressBar.h"

#include <iostream>
#include <iomanip>

void ProgressBar::update(float percentage)
{
    m_percentage = percentage;
}

void ProgressBar::show() const
{
    for (int i = 0; i <= m_width; ++i) {
        std::cout << "\r" << "archiving... " << "[";

        int current_width = widthFromPercentage();
        for (int j = 0; j <= m_width; ++j) {
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

        std::cout << "] " << std::fixed << std::setprecision(1) << m_percentage << "% complete" << std::flush;
    }
}

int ProgressBar::widthFromPercentage() const
{
    return (m_width * m_percentage) / 100;
}

