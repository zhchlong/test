#include "bind.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void Bind::init() {
            // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("bind");

        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&Bind::getPath, this);
        SVGIPath->D.bind(_getPath);
    }    // 拷贝
    ComponentAbstract &Bind::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Bind &>(comp);

        return *this;
    }
    // 序列化，并记录已操作的
    void Bind::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);

    }
    // 反序列化
    ComponentAbstract &Bind::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        return *this;
    }
    //// Basics虚接口
    void Bind::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
       Rectangle::moveCorePoint(id, dx, dy);
        onChanged(); // 更新事件
    }

  ////Bind interface
    const std::string Bind::getPath() const {
        auto p0 = createPoint(getX(), getY());
        auto p1 = createPoint(getX(), getY()+getHeight());
        auto p2 = createPoint(getX(), getY()+getHeight()*0.5);
        auto p3 = createPoint(getX()+getWidth()*0.2, getY()+getHeight()*0.5);
        auto p4 = createPoint(getX()+getWidth()*0.2, getY()+getHeight()*0.5);
        auto p5 = createPoint(getX()+getWidth()*0.2, getY()+getHeight()*0.5);
        auto p6 = createPoint(getX()+getWidth(), getY()+getHeight()*0.5);

        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "L " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "M " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "L " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "M " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "A " << getWidth()*0.4 << " " << getHeight()*0.5<< " " << 0 << " " << 0  <<" "<< 0 << " " << p6.get_x() << " " << p6.get_y() << " ";

        ss << "M " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "A " << getWidth()*0.4 << " " << getHeight()*0.5<< " " << 0 << " " << 0  <<" "<< 1 << " " << p6.get_x() << " " << p6.get_y() << " ";

        return ss.str();

    }
}