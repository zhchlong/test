#include "element.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void Element::init() {
            // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("element");

        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&Element::getPath, this);
        SVGIPath->D.bind(_getPath);
    }    // 拷贝
    ComponentAbstract &Element::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Element &>(comp);


        return *this;
    }
    // 序列化，并记录已操作的
    void Element::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &Element::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        return *this;
    }
    //// Basics虚接口
    void Element::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
       Rectangle::moveCorePoint(id, dx, dy);
        onChanged(); // 更新事件
    }

  ////Element interface
    const std::string Element::getPath() const {
        auto p0 = createPoint(getX()+getWidth()*0.125, getY());
        auto p1 = createPoint(getX()+getWidth(), getY());
        auto p2 = createPoint(getX()+getWidth(), getY()+getHeight());
        auto p3 = createPoint(getX()+getWidth()*0.125, getY()+getHeight());
        auto p4 = createPoint(getX()+getWidth()*0.125, getY());
        auto p5 = createPoint(getX(), getY()+getHeight()*0.2);
        auto p6 = createPoint(getX()+getWidth()*0.25, getY()+getHeight()*0.2);
        auto p7 = createPoint(getX()+getWidth()*0.25, getY()+getHeight()*0.4);
        auto p8 = createPoint(getX(), getY()+getHeight()*0.4);
        auto p9 = createPoint(getX(), getY()+getHeight()*0.2);
        auto p10 = createPoint(getX(), getY()+getHeight()*0.6);
        auto p11 = createPoint(getX()+getWidth()*0.25, getY()+getHeight()*0.6);
        auto p12 = createPoint(getX()+getWidth()*0.25, getY()+getHeight()*0.8);
        auto p13 = createPoint(getX(), getY()+getHeight()*0.8);
        auto p14 = createPoint(getX(), getY()+getHeight()*0.6);
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "L " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "L " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "L " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "M " << p5.get_x() << " " << p5.get_y() << " ";
        ss << "L " << p6.get_x() << " " << p6.get_y() << " ";
        ss << "L " << p7.get_x() << " " << p7.get_y() << " ";
        ss << "L " << p8.get_x() << " " << p8.get_y() << " ";
        ss << "L " << p9.get_x() << " " << p9.get_y() << " ";
        ss << "M " << p10.get_x() << " " << p10.get_y() << " ";
        ss << "L " << p11.get_x() << " " << p11.get_y() << " ";
        ss << "L " << p12.get_x() << " " << p12.get_y() << " ";
        ss << "L " << p13.get_x() << " " << p13.get_y() << " ";
        ss << "L " << p14.get_x() << " " << p14.get_y() << " ";
        return ss.str();

    }
}