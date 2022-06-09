#include "frame.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void Frame::init() {
        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("frame");

        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
//        SVGIPathA = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        abc = createCorePoint("abc", getX() + getWidth() * 0.2, getY() + getHeight() * 0.2);
        abc->setColor("orange");
        abc->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if (nx < (getX())) {
                abc->setX(getX());
            }
            if (nx > getX() + getWidth()) {
                abc->setX(getX() + getWidth());
            }
            if (ny < getY()) {
                abc->setY(getY());
            }
            if (ny > getY() + getHeight()) {
                abc->setY(getY() + getHeight());
            }

        });
        corePoints[abc->getId()] = abc;
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&Frame::getPath, this);
        SVGIPath->D.bind(_getPath);
    }    // 拷贝
    ComponentAbstract &Frame::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Frame &>(comp);
        // 拷贝关键点位置
        *abc = *(p.abc);

        return *this;
    }

    // 序列化，并记录已操作的
    void Frame::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }

    // 反序列化
    ComponentAbstract &Frame::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);
        // 注册关键点
        abc = corePoints["abc"];

        return *this;
    }

    //// Basics虚接口
    void Frame::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
        double disY0 = abc->getY() - getY(); // 记录控制点到矩形上边的距离
        double disX0 = abc->getX() - getX();
        if (id == "abc") { // 移动控制点
            corePointMoving = true; // 开启更新锁
            *abc += createPoint(dx, dy);
            corePointMoving = false;
        } else {
            Rectangle::moveCorePoint(id, dx, dy);
            if (getX() + disX0 > getX() + getWidth()) disX0 = getX() + getWidth() - getX();
            if (getY() + disY0 > getY() + getHeight()) disY0 = getY() + getHeight() - getY();
            *abc = createPoint(getX() + disX0, getY() + disY0); // 设置新的坐标
            *abc = createPoint(getX() + disX0, getY() + disY0);
        }
        onChanged(); // 更新事件
    }

    ////Frame interface
    const std::string Frame::getPath() const {
        auto p0 = createPoint(getX(), abc->getY());
        auto p1 = createPoint(abc->getX(), abc->getY());
        auto p2 = createPoint(abc->getX(), getY());
        auto p3 = createPoint(getX(), getY());
        auto p4 = createPoint(getX() + getWidth(), getY());
        auto p5 = createPoint(getX() + getWidth(), getY() + getHeight());
        auto p6 = createPoint(getX(), getY() + getHeight());
        std::stringstream ss;

        ss << "M " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "L " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "L " << p5.get_x() << " " << p5.get_y() << " ";
        ss << "L " << p6.get_x() << " " << p6.get_y() << " ";
        ss << "L " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "L " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "L " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p0.get_x() << " " << p0.get_y() << " ";
        return ss.str();

    }
}