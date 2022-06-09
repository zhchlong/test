//
// Created by l'l on 2022/5/29.
//

#include "subTopic.h"
namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void SubTopic::init() {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("sub_topic");
        // 维护图形SVG
        Rectangle::move(200,30);
        Rectangle::moveCorePoint("RB", -30, -10);
        SVGIG->remove(SVGIRect);
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        SVGIG->add(SVGIRect);

        // 初始化关键点
        startPoint = createCorePoint("start",100,200);
        setCorePoints({startPoint});


        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&SubTopic::getPath, this);
        SVGIPath->D.bind(_getPath);
    }
    // 拷贝
    ComponentAbstract &SubTopic::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const SubTopic &>(comp);
        // 拷贝关键点位置
        *startPoint = *(p.startPoint);
        return *this;
    }
    // 序列化，并记录已操作的
    void SubTopic::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &SubTopic::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        // 注册关键点
        startPoint = corePoints["start"];

        return *this;
    }

    //// Basics虚接口
    void SubTopic::moveCorePoint(const std::string &id, const double &dx, const double &dy) {

        if(id == "start"){
            *startPoint += createPoint(dx,dy);
        }
        else{
            Rectangle::moveCorePoint(id, dx, dy);
        }
        onChanged(); // 更新事件
    }

    // 计算路径
    const std::string SubTopic::getPath() const {

        if(startPoint->getX()+10 <= getX()){
            auto e = createPoint(getX(),getY()+getHeight()/2);
            auto s = *startPoint;
            auto m = createPoint((s.getX()+e.get_x())/2,(s.getY()+e.get_y())/2);
            std::stringstream ss;
            ss<<" M "<<s.getX()<<" "<<s.getY()<<" ";
            ss<<" Q "<<s.getX()+10<<" "<<s.getY()<<" "<<m.get_x()<<" "<<m.get_y();
            ss<<" Q "<<e.get_x()-10<<" "<<e.get_y()<<" "<<e.get_x()<<" "<<e.get_y();
            return ss.str();
        }
        else{
            auto e = createPoint(getX()+getWidth(),getY()+getHeight()/2);
            auto s = *startPoint;
            auto m = createPoint((s.getX()+e.get_x())/2,(s.getY()+e.get_y())/2);
            std::stringstream ss;
            ss<<" M "<<s.getX()<<" "<<s.getY()<<" ";
            ss<<" Q "<<e.get_x()+10<<" "<<s.getY()<<" "<<e.get_x()+10<<" "<<m.get_y();
            ss<<" Q "<<e.get_x()+10<<" "<<e.get_y()<<" "<<e.get_x()<<" "<<e.get_y();
            return ss.str();
        }

    }
}