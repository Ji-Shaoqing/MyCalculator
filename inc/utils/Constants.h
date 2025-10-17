/**
 * @file Constants.h
 * @brief 应用程序常量定义
 * @author Jisq
 * @version 1.0
 * @date 2025
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Calculator {

/**
 * @class Constants
 * @brief 应用程序常量
 */
class Constants
{
public:
    // 显示相关常量
    static constexpr int MAX_DISPLAY_LENGTH = 15;       // 最大显示长度
    static constexpr int DISPLAY_FONT_SIZE = 24;        // 显示字体大小
    static constexpr int BUTTON_FONT_SIZE = 16;         // 按钮字体大小

    // 计算相关常量
    static constexpr double MAX_CALCULATION_VALUE = 1e15;   // 最大计算值
    static constexpr double MIN_CALCULATION_VALUE = -1e15;  // 最小计算值

    // 界面尺寸常量
    static constexpr int WINDOW_WIDTH = 300;            // 窗口宽度
    static constexpr int WINDOW_HEIGHT = 400;           // 窗口高度
    static constexpr int BUTTON_WIDTH = 60;             // 按钮宽度
    static constexpr int BUTTON_HEIGHT = 50;            // 按钮高度
    static constexpr int LAYOUT_SPACING = 4;            // 布局间距
    static constexpr int LAYOUT_MARGIN = 8;             // 布局边距

    // 样式相关
    static const char* DEFAULT_STYLE;                   // 默认样式表路径
    static const char* DARK_STYLE;                      // 深色样式表路径
};

} // namespace Calculator

#endif // CONSTANTS_H