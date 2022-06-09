#include "rectangle.h"
#include "../canvas.h"

namespace LewzenServer {
    //// 注册
    bool Rectangle::registered = false;
    // 注册接口
    void Rectangle::registering() {
        registered = true;
        Register::addEvent("get_rect", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<Rectangle>(cursor); // 动态类型转换
                double x = comp->getX(), y = comp->getY(), width = comp->getWidth(), height = comp->getHeight();
                json j; j["x"] = x, j["y"] = y, j["width"] = width, j["height"] = height;
                param["rect"] = j;
                param["status"] = SUCCEED;
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                bool matched = false;
                json j;
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<Rectangle>(cursor); // 动态类型转换
                    double x = comp->getX(), y = comp->getY(), width = comp->getWidth(), height = comp->getHeight();
                    if (!matched) {
                        j["x"] = x, j["y"] = y, j["width"] = width, j["height"] = height;
                        matched = true;
                    } else { // 多值
                        json b; b["x"] = x, b["y"] = y, b["width"] = width, b["height"] = height;
                        if (j != b) {
                            matched = false;
                            break;
                        }
                    }
                }
                if (matched) {
                    param["rect"] = j;
                    param["status"] = SUCCEED;
                } else param["status"] = MULTIVL;
            });
            return param;
        });
        Register::addEvent("set_rect", [&](json &param) {
            double x = param["rect"]["x"], y = param["rect"]["y"], width = param["rect"]["width"], height = param["rect"]["height"];
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<Rectangle>(cursor); // 动态类型转换
                // 计算两点的移动距离
                auto p1 = comp->vectorToCanvas(comp->createPoint(x, y) - *(comp->LT));
                auto p2 = comp->vectorToCanvas(comp->createPoint(x + width, y + height) - *(comp->RB));
                // 移动两点
                comp->moveCorePoint("LT", p1.get_x(), p1.get_y());
                comp->moveCorePoint("RB", p2.get_x(), p2.get_y());
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<Rectangle>(cursor); // 动态类型转换
                    // 计算两点的移动距离
                    auto p1 = comp->vectorToCanvas(comp->createPoint(x, y) - *(comp->LT));
                    auto p2 = comp->vectorToCanvas(comp->createPoint(x + width, y + height) - *(comp->RB));
                    // 移动两点
                    comp->moveCorePoint("LT", p1.get_x(), p1.get_y());
                    comp->moveCorePoint("RB", p2.get_x(), p2.get_y());
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("cover_children", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<Rectangle>(cursor); // 动态类型转换
                comp->resizeByChildren();
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<Rectangle>(cursor); // 动态类型转换
                    comp->resizeByChildren();
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
    }

    //// 基本
    // 构造
    Rectangle::Rectangle() {
        if (!registered) registering(); // 注册
        addModuleTypes(module_type); // 添加模块类型
    }

    //// 通用虚接口
    // 非构造初始化，初始化组件在(x, y)
    void Rectangle::init() {
        // 设置类型
        std::cout << "ar\n\n";
        setType("rectangle");
        std::cout << "ar\n\n";
        // 父类初始化
        ComponentRotatable::init();
        ComponentWritable::init();
        ComponentStylized::init();
        std::cout << "ar\n\n";
        // 添加图形SVG
        SVGIRect = std::make_shared<Lewzen::SVGIRect>();
        SVGIG->add(SVGIRect);
        std::cout << "ar\n\n";
        // 初始化关键点表
        LT = createCorePoint("LT", 0, 0),
        L = createCorePoint("L", 0, 50),
        LB = createCorePoint("LB", 0, 100),
        B = createCorePoint("B", 100, 100),
        RB = createCorePoint("RB", 200, 100),
        R = createCorePoint("R", 200, 50),
        RT = createCorePoint("RT", 200, 0),
        T = createCorePoint("T", 100, 0);
        LT->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            LB->setX(nx); RT->setY(ny);
            *L = (*LT + *LB) * 0.5;
            *T = (*LT + *RT) * 0.5;
        });
        LB->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            LT->setX(nx); RB->setY(ny);
            *L = (*LT + *LB) * 0.5;
            *B = (*LB + *RB) * 0.5;
        });
        RB->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            RT->setX(nx); LB->setY(ny);
            *R = (*RT + *RB) * 0.5;
            *B = (*LB + *RB) * 0.5;
        });
        RT->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            RB->setX(nx); LT->setY(ny);
            *R = (*RT + *RB) * 0.5;
            *T = (*LT + *RT) * 0.5;
        });
        L->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            LT->setX(nx), LB->setX(nx);
        });
        B->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            LB->setY(ny), RB->setY(ny);
        });
        R->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            RT->setX(nx), RB->setX(nx);
        });
        T->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            LT->setY(ny), RT->setY(ny);
        });
        // 注册关键点
        setCorePoints({ LT, L, LB, B, RB, R, RT, T });

        // 绑定图形属性
        std::function<double()> _getX = std::bind(&Rectangle::getX, this);
        std::function<double()> _getY = std::bind(&Rectangle::getY, this);
        std::function<double()> _getWidth = std::bind(&Rectangle::getWidth, this);
        std::function<double()> _getHeight = std::bind(&Rectangle::getHeight, this);
        SVGIRect->X.bind(_getX);
        SVGIRect->Y.bind(_getY);
        SVGIRect->Width.bind(_getWidth);
        SVGIRect->Height.bind(_getHeight);
        std::cout << "ar\n\n";
        // 默认样式
        setStyle("stroke: black; fill: white; stroke-width: 1px;");std::cout << "ar\n\n";
    }
    // 拷贝
    ComponentAbstract &Rectangle::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        ComponentRotatable::operator=(comp);
        ComponentWritable::operator=(comp);
        ComponentStylized::operator=(comp);
        
        auto &p = dynamic_cast<const Rectangle &>(comp);        
        // 拷贝关键点位置
        *LT = *(p.LT),
        *L = *(p.L),
        *LB = *(p.LB),
        *B = *(p.B),
        *RB = *(p.RB),
        *R = *(p.R),
        *RT = *(p.RT),
        *T = *(p.T);

        return *this;
    }
    // 序列化，并记录已操作的
    void Rectangle::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        ComponentRotatable::serialize(j, processed);
        ComponentWritable::serialize(j, processed);
        ComponentStylized::serialize(j, processed);

        // (无额外私有内容)
    }
    // 反序列化
    ComponentAbstract &Rectangle::operator=(const json &j) {
        // 父类反序列化 (倒序)
        ComponentStylized::operator=(j);
        ComponentWritable::operator=(j);
        ComponentRotatable::operator=(j);

        // 注册关键点
        LT = corePoints["LT"],
        L = corePoints["L"],
        LB = corePoints["LB"],
        B = corePoints["B"],
        RB = corePoints["RB"],
        R = corePoints["R"],
        RT = corePoints["RT"],
        T = corePoints["T"];

        return *this;
    }

    //// Basics虚接口
    // 移动关键点
    void Rectangle::moveCorePoint(const std::string &id, const double &_dx, const double &_dy) {
        auto delta = vectorFromCanvas(Lewzen::canvas_point(_dx, _dy)); // 计算组件坐标系的Δ
        double dx = delta.get_x(), dy = delta.get_y();
        auto lastCenter = getCenter(); double width = getWidth(), height = getHeight();
        corePointMoving = true; // 更新锁
        // 具体更新
        if (id == "L") *L += createPoint(dx, 0);
        if (id == "R") *R += createPoint(dx, 0);
        if (id == "T") *T += createPoint(0, dy);
        if (id == "B") *B += createPoint(0, dy);
        if (id == "LT") *LT += createPoint(dx, dy);
        if (id == "LB") *LB += createPoint(dx, dy);
        if (id == "RT") *RT += createPoint(dx, dy);
        if (id == "RB") *RB += createPoint(dx, dy);
        corePointMoving = false; // 更新锁
        onRotateCenterChanged(); // 旋转中心变化响应
        onScaleChanged(lastCenter, getWidth() / width, getHeight() / height); // 大小变化响应
        onChanged(); // 更新事件
    }

    //// Scalable接口
    void Rectangle::scale(const double &scaleX, const double &scaleY) {
        double sx = (scaleX - 1) * (R->getX() - L->getX()), sy = (scaleY - 1) * (B->getY() - T->getY());
        auto delta = vectorToCanvas(createPoint(sx, sy));
        moveCorePoint("RB", delta.get_x(), delta.get_y());
    }

    //// Flippable接口
    void Rectangle::flip(const double &a, const double &b, const double &c) {
        auto A = Lewzen::canvas_point(0, 0), B = Lewzen::canvas_point(0, 0);
        auto C = getCenter();
        double theta = 0;
        if (a == 0) { double ly = -c / b; A = Lewzen::canvas_point(0, ly), B = Lewzen::canvas_point(1, ly); theta = 0;}
        else if (b == 0) { double lx = -c / a; A = Lewzen::canvas_point(lx, 0), B = Lewzen::canvas_point(lx, 1); theta = ComponentRotatable::PI / 2; }
        else { double ly = -c / b; double lx = -c / a; A = Lewzen::canvas_point(lx, 0), B = Lewzen::canvas_point(0, ly); theta = std::atan(-b / a); }
        auto FlippedC = Lewzen::line_symmetric(C, A, B);
        // 等价于移动到对称位置然后旋转
        moveTo(FlippedC.get_x(), FlippedC.get_y());
        setTheta(theta * 2- getTheta());
        // 响应翻转
        onFlipped(a, b, c);
    }

    //// Writable虚接口
    const ComponentWritable::WriteArea Rectangle::getWriteArea() {
        return {
            getX(),
            getY(),
            getWidth(),
            getHeight()
        };
    }

    //// 矩形接口
    void Rectangle::resizeByChildren() {
        double minX, minY, maxX, maxY; bool did;
        for (auto &c : getChildren()) {
            for (auto &p : c->getCorePoints()) {
                if (auto pp = p.lock()) {
                    auto pc = (*pp)(getCoordinateSystem());
                    if (!did) {
                        minX = maxX = pc.get_x();
                        minY = maxY = pc.get_y();
                        did = true;
                    } else {
                        minX = std::min(pc.get_x(), minX);
                        maxX = std::max(pc.get_x(), maxX);
                        minY = std::min(pc.get_y(), minY);
                        maxY = std::max(pc.get_y(), maxY);
                    }
                }
            }            
        }
        // 计算两点的移动距离
        auto p1 = vectorToCanvas(createPoint(minX, minY) - *LT);
        auto p2 = vectorToCanvas(createPoint(maxX, maxY) - *RB);
        // 移动两点
        moveCorePoint("LT", p1.get_x(), p1.get_y());
        moveCorePoint("RB", p2.get_x(), p2.get_y());
    }
    double Rectangle::getX() const {
        return std::min(L->getX(), R->getX());
    }
    double Rectangle::getY() const {
        return std::min(T->getY(), B->getY());
    }
    double Rectangle::getWidth() const {
        return std::abs(L->getX() - R->getX());
    }
    double Rectangle::getHeight() const {
        return std::abs(T->getY() - B->getY());
    }
}