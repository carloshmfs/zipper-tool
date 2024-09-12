#pragma once

class ProgressBar {
public:
    void update(float);
    void show() const;

private:
    int widthFromPercentage() const;

    float m_percentage;
    int m_width = 70;
};
