#include "rectangle_text.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void RectangleText::init() {
            // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("rectangle_text");
        // 维护图形SVG
//        SVGIRect->Fill="white";
        SVGIRect->Opacity=0;
        setHTML("<p>Text</p>");
        Rectangle::moveCorePoint("RB", -100, -50); // 将区域变更为方形

    }    // 拷贝
    ComponentAbstract &RectangleText::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const RectangleText &>(comp);
        return *this;
    }
    // 序列化，并记录已操作的
    void RectangleText::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &RectangleText::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);
        return *this;
    }
//
//    //// Writable虚接口
//    const ComponentWritable::WriteArea RectangleText::getWriteArea() {
//        return {
//                getX(),
//                getY(),
//                getWidth(),
//                getHeight()
//        };
//    }
    //// Basics虚接口
    void RectangleText::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
       Rectangle::moveCorePoint(id, dx, dy);
        onChanged(); // 更新事件
    }

  ////RectangleText interface
    const std::string RectangleText::getPath() const {
        auto p0 = createPoint(getX(), getY());
        auto p1 = createPoint(getX()+getWidth(), getY());
        auto p2 = createPoint(getX()+getWidth(), getY()+getHeight());
        auto p3 = createPoint(getX(), getY()+getHeight());
        auto p4 = createPoint(getX(), getY());
        auto p5 = createPoint(getX(), getY());
        auto p6 = createPoint(getX(), getY()+getHeight());
        auto p7 = createPoint(getX()+getWidth(), getY());
        auto p8 = createPoint(getX()+getWidth(), getY()+getHeight());
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "L " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "L " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "L " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "M " << p5.get_x() << " " << p5.get_y() << " ";
        ss << "L " << p6.get_x() << " " << p6.get_y() << " ";
        ss << "M " << p7.get_x() << " " << p7.get_y() << " ";
        ss << "L " << p8.get_x() << " " << p8.get_y() << " ";
        return ss.str();

    }
}