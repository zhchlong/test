//
// Created by l'l on 2022/5/23.
//

#ifndef MAIN_CPP_TRAPEZOID_H
#define MAIN_CPP_TRAPEZOID_H

#include "../comp/rectangle.h"

namespace LewzenServer {
    class Trapezoid : virtual public Rectangle {
    protected:
        // 实际SVGI
        std::shared_ptr<Lewzen::SVGIPath> SVGIPath;
        // 额外的关键点
        std::shared_ptr<CorePoint> Control;
    public:
        //// 通用虚接口
        // 非构造初始化
        virtual void init() override;
        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp) override;
        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed) override;
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j) override;

        //// Basics虚接口
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy) override;

        //// IsometricCube接口
        // 计算路径
        const std::string getPath() const;
    };
}


#endif //MAIN_CPP_TRAPEZOID_H
