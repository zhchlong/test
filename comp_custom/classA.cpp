//
// Created by l'l on 2022/6/7.
//

#include "classA.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void ClassA::init() {


        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("classes");
        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0);
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 初始化关键点

        ControlUp = createCorePoint("ControlUp", getX() + getWidth() / 2, getY() + getHeight() * 0.16);
        ControlDown = createCorePoint("ControlDown", getX() + getWidth() / 2, getY() + getHeight() * 0.6);
        ControlUp->setColor("orange");
        ControlDown->setColor("orange");

        ControlUp->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if (ny < getY()) {
                ControlUp->setY(getY());
            }
            if (ny > getY() + getHeight()) {
                ControlUp->setY(getY() + getHeight());
            }
        });

        ControlDown->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if (ny > getY() + getHeight()) {
                ControlDown->setY(getY() + getHeight());
            }
            if (ny < getY()) {
                ControlDown->setY(getY());
            }
        });
        setCorePoints({ControlUp, ControlDown});


        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&ClassA::getPath, this);
        SVGIPath->D.bind(_getPath);
    }

    // 拷贝
    ComponentAbstract &ClassA::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const ClassA &>(comp);
        // 拷贝关键点位置
        *ControlUp = *(p.ControlUp);
        *ControlDown = *(p.ControlDown);

        return *this;
    }

    // 序列化，并记录已操作的
    void ClassA::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);

    }

    // 反序列化
    ComponentAbstract &ClassA::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        // 注册关键点

        ControlUp = corePoints["ControlUp"];
        ControlDown = corePoints["ControlDown"];

        return *this;
    }

    //// Basics虚接口
    void ClassA::moveCorePoint(const std::string &id, const double &dx, const double &dy) {

        double disY0 = ControlUp->getY() - getY(); // 记录控制点到矩形上边的距离

        double disY1 = ControlDown->getY() - getY(); // 记录控制点到矩形上边的距离

        if (id == "ControlUp") { // 移动控制点
            corePointMoving = true; // 开启更新锁
            *ControlUp += createPoint(0, dy);
            corePointMoving = false;
            if (ControlUp->getY() > ControlDown->getY()) {
                ControlUp->setY(ControlDown->getY());
            }
        } else if (id == "ControlDown") { // 移动控制点
            corePointMoving = true; // 开启更新锁
            *ControlDown += createPoint(0, dy);
            corePointMoving = false;
            if (ControlDown->getY() < ControlUp->getY()) { ControlDown->setY(ControlUp->getY()); }
        } else {
            Rectangle::moveCorePoint(id, dx, dy);
            if (getY() + disY0 > getY() + getHeight()) disY0 = getY() + getHeight() - getY();
            *ControlUp = createPoint(getX() + getWidth() * 0.5, getY() + disY0); // 设置新的坐标
            if (getY() + disY1 > getY() + getHeight()) disY1 = getY() + getHeight() - getY();
            *ControlDown = createPoint(getX() + getWidth() * 0.5, getY() + disY1); // 设置新的坐标
        }
        onChanged(); // 更新事件
    }

    //// IsometricCube接口
    // 计算路径
    const std::string ClassA::getPath() const {
        auto p0 = createPoint(getX(), getY());
        auto p1 = createPoint(getX() + getWidth(), getY());
        auto p2 = createPoint(getX() + getWidth(), getY() + getHeight());
        auto p3 = createPoint(getX(), getY() + getHeight());
        auto p4 = createPoint(getX(), getY());
        auto p5 = createPoint(getX(), ControlUp->getY());
        auto p6 = createPoint(getX() + getWidth(), ControlUp->getY());
        auto p7 = createPoint(getX(), ControlDown->getY());
        auto p8 = createPoint(getX() + getWidth(), ControlDown->getY());
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
