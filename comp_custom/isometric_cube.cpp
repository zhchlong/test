#include "isometric_cube.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void IsometricCube::init() {
        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("isometric_cube");


        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 初始化关键点
        Control = createCorePoint("Control", 0, 20);
        Control->setColor("orange");
        Control->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if (ny > getY() + getHeight() / 2) Control->setY(L->getY()); // 不允许超过高度的一半
            if (ny < getY()) Control->setY(getY()); // 不允许低于矩形的Y坐标
        });
        // 注册关键点
        corePoints[Control->getId()] = Control;

        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&IsometricCube::getPath, this);
        SVGIPath->D.bind(_getPath);
    }
    // 拷贝
    ComponentAbstract &IsometricCube::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const IsometricCube &>(comp);
        
        // 拷贝关键点位置
        *Control = *(p.Control);

        return *this;
    }
    // 序列化，并记录已操作的
    void IsometricCube::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &IsometricCube::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        // 注册关键点
        Control = corePoints["Control"];

        return *this;
    }

    //// Basics虚接口
    void IsometricCube::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
        double d = Control->getY() - getY(); // 记录控制点到矩形上边的距离
        if (id == "Control") { // 移动控制点
            corePointMoving = true; // 开启更新锁
            *Control += createPoint(0, dy); // 只允许纵向移动
            corePointMoving = false;
        } else { // 移动其他点
            Rectangle::moveCorePoint(id, dx, dy);
            // 更新控制点
            if (d > getHeight() / 2) d = getHeight() / 2; // 不允许超过高度的一半
            *Control = createPoint(getX(), getY() + d); // 设置新的坐标
        }
        onChanged(); // 更新事件
    }

    //// IsometricCube接口
    // 计算路径
    const std::string IsometricCube::getPath() const {
        auto t = createPoint(getX() + getWidth() / 2, getY());
        auto tl = createPoint(getX(), Control->getY());
        auto tr = createPoint(getX() + getWidth(), Control->getY());
        auto c = createPoint(getX() + getWidth() / 2, 2 * Control->getY() - getY());
        auto b = createPoint(getX() + getWidth() / 2, getY() + getHeight());
        auto bl = createPoint(getX(), getY() + getHeight() - (Control->getY() - getY()));
        auto br = createPoint(getX() + getWidth(), getY() + getHeight() - (Control->getY() - getY()));

        std::stringstream ss;
    
        ss << "M " << c.get_x() << " " << c.get_y() << " ";
        ss << "L " << tl.get_x() << " " << tl.get_y() << " ";
        ss << "L " << t.get_x() << " " << t.get_y() << " ";
        ss << "L " << tr.get_x() << " " << tr.get_y() << " ";
        ss << "L " << c.get_x() << " " << c.get_y() << " ";
        ss << "L " << b.get_x() << " " << b.get_y() << " ";

        ss << "L " << br.get_x() << " " << br.get_y() << " ";
        ss << "L " << tr.get_x() << " " << tr.get_y() << " ";
        ss << "L " << c.get_x() << " " << c.get_y() << " ";

        ss << "M " << tl.get_x() << " " << tl.get_y() << " ";
        ss << "L " << bl.get_x() << " " << bl.get_y() << " ";
        ss << "L " << b.get_x() << " " << b.get_y() << " ";
        ss << "L " << c.get_x() << " " << c.get_y() << " ";
        ss << "L " << tl.get_x() << " " << tl.get_y() << " ";
//        ss << "L " << br.get_x() << " " << br.get_y() << " ";
//        ss << "L " << tr.get_x() << " " << tr.get_y() << " ";

        return ss.str();
    }
}