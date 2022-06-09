#include "lifeline.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void Lifeline::init() {
            // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("lifeline");

        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&Lifeline::getPath, this);
        SVGIPath->D.bind(_getPath);
    }    // 拷贝
    ComponentAbstract &Lifeline::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Lifeline &>(comp);

        return *this;
    }
    // 序列化，并记录已操作的
    void Lifeline::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &Lifeline::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        return *this;
    }
    //// Basics虚接口
    void Lifeline::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
       Rectangle::moveCorePoint(id, dx, dy);
        onChanged(); // 更新事件
    }

  ////Lifeline interface
    const std::string Lifeline::getPath() const {
        auto p0 = createPoint(getX(), getY());
        auto p1 = createPoint(getX()+getWidth(), getY());
        auto p2 = createPoint(getX()+getWidth(), getY()+padding);
        auto p3 = createPoint(getX(), getY()+padding);
        auto p6 = createPoint(getX(), getY());

        auto p4 = createPoint(getX()+getWidth()*0.5, getY()+padding);
        auto p5 = createPoint(getX()+getWidth()*0.5, getY()+getHeight());
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "L " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "L " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "L " << p6.get_x() << " " << p6.get_y() << " ";

        ss << "M " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "L " << p5.get_x() << " " << p5.get_y() << " ";
        return ss.str();

    }
}