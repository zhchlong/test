//
// Created by l'l on 2022/5/16.
//

#include "line.h"
#include "../canvas.h"

namespace LewzenServer {

    //// 注册
    bool Line::registered = false;

    void Line::registering() {
        registered = true;
        Register::addEvent("get_start", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
//                                     double x = comp->getX(), y = comp->getY(), width = comp->getWidth(), height = comp->getHeight();
                                     auto startP = comp->getStartPoint();
                                     json j;
                                     j["x"] = startP.getX(), j["y"] = startP.getY();
                                     param["start"] = j;
                                     param["status"] = SUCCEED;
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     bool matched = false;
                                     json j;
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         auto startP = comp->getStartPoint();
                                         if (!matched) {
                                             j["x"] = startP.getX(), j["y"] = startP.getY();
                                             matched = true;
                                         } else { // 多值
                                             json b;
                                             b["x"] = startP.getX(), b["y"] = startP.getY();
                                             if (j != b) {
                                                 matched = false;
                                                 break;
                                             }
                                         }
                                     }
                                     if (matched) {
                                         param["start"] = j;
                                         param["status"] = SUCCEED;
                                     } else param["status"] = MULTIVL;
                                 });
            return param;
        });

        Register::addEvent("get_end", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
//                                     double x = comp->getX(), y = comp->getY(), width = comp->getWidth(), height = comp->getHeight();

                                     auto endP = comp->getEndPoint();
                                     json j;
                                     j["x"] = endP.getX(), j["y"] = endP.getY();
                                     param["end"] = j;
                                     param["status"] = SUCCEED;
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     bool matched = false;
                                     json j;
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         auto endP = comp->getEndPoint();
                                         if (!matched) {
                                             j["x"] = endP.getX(), j["y"] = endP.getY();
                                             matched = true;
                                         } else { // 多值
                                             json b;
                                             b["x"] = endP.getX(), b["y"] = endP.getY();
                                             if (j != b) {
                                                 matched = false;
                                                 break;
                                             }
                                         }
                                     }
                                     if (matched) {
                                         param["end"] = j;
                                         param["status"] = SUCCEED;
                                     } else param["status"] = MULTIVL;
                                 });
            return param;
        });
        Register::addEvent("set_start", [&](json &param) {
            double x = param["x"], y = param["y"];
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     // 计算两点的移动距离
                                     auto p1 = comp->vectorToCanvas(comp->createPoint(x, y) - *(comp->startPoint));
                                     // 移动两点
                                     comp->moveCorePoint("start", p1.get_x(), p1.get_y());
//
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         // 计算两点的移动距离
                                         auto p1 = comp->vectorToCanvas(comp->createPoint(x, y) - *(comp->startPoint));
//                                         auto p2 = comp->vectorToCanvas(comp->createPoint(x + width, y + height) - *(comp->RB));
                                         // 移动两点
                                         comp->moveCorePoint("start", p1.get_x(), p1.get_y());
//                                         comp->moveCorePoint("RB", p2.get_x(), p2.get_y());
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });

        Register::addEvent("set_end", [&](json &param) {
            double x = param["x"], y = param["y"];
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     // 计算两点的移动距离
                                     auto p1 = comp->vectorToCanvas(comp->createPoint(x, y) - *(comp->endPoint));
                                     // 移动两点
                                     comp->moveCorePoint("end", p1.get_x(), p1.get_y());
//
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         // 计算两点的移动距离
                                         auto p1 = comp->vectorToCanvas(comp->createPoint(x, y) - *(comp->endPoint));
//                                         auto p2 = comp->vectorToCanvas(comp->createPoint(x + width, y + height) - *(comp->RB));
                                         // 移动两点
                                         comp->moveCorePoint("end", p1.get_x(), p1.get_y());
//                                         comp->moveCorePoint("RB", p2.get_x(), p2.get_y());
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });

        Register::addEvent("get_start_arrow", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     auto startA = comp->getStartArrow();

                                     param["start_arrow"] = startA;
                                     param["status"] = SUCCEED;
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     bool matched = false;
                                     json j;
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         auto startA = comp->getStartArrow();
                                         if (!matched) {
                                             j["start_arrow"] = startA;
                                             matched = true;
                                         } else { // 多值
                                             json b;
                                             b["start_arrow"] = startA;
                                             if (j != b) {
                                                 matched = false;
                                                 break;
                                             }
                                         }
                                     }
                                     if (matched) {
                                         param["start_arrow"] = j["start_arrow"];
                                         param["status"] = SUCCEED;
                                     } else param["status"] = MULTIVL;
                                 });
            return param;
        });

        Register::addEvent("get_end_arrow", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     auto endA = comp->getEndArrow();

                                     param["end_arrow"] = endA;
                                     param["status"] = SUCCEED;
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     bool matched = false;
                                     json j;
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         auto endA = comp->getEndArrow();
                                         if (!matched) {
                                             j["end_arrow"] = endA;
                                             matched = true;
                                         } else { // 多值
                                             json b;
                                             b["end_arrow"] = endA;
                                             if (j != b) {
                                                 matched = false;
                                                 break;
                                             }
                                         }
                                     }
                                     if (matched) {
                                         param["end_arrow"] = j["end_arrow"];
                                         param["status"] = SUCCEED;
                                     } else param["status"] = MULTIVL;
                                 });
            return param;
        });

        Register::addEvent("set_start_arrow", [&](json &param) {
            auto ar = param["start_arrow"];
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     comp->setStartArrow(ar);
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         comp->setStartArrow(ar);
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });

        Register::addEvent("set_end_arrow", [&](json &param) {
            auto ar = param["end_arrow"];
            // 切换器
            //std::cout<<"ar "<<ar<<std::endl;
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     //std::cout<<"ar \n";
                                     comp->setEndArrow(ar);
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         comp->setEndArrow(ar);
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("set_line_type", [&](json &param) {
            auto lt = param["line_type"];
            // 切换器
            //std::cout<<"lt "<<lt<<std::endl;
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     //std::cout<<"lt \n";
                                     comp->setLineType(lt);
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         comp->setLineType(lt);
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("on_offset", [&](json &param) {
            // 切换器
            //std::cout<<"lt "<<lt<<std::endl;
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     //std::cout<<"lt \n";
                                     comp->onOffset();
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         comp->onOffset();
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });

        Register::addEvent("close_offset", [&](json &param) {
            // 切换器
            //std::cout<<"lt "<<lt<<std::endl;
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     comp->closeOffset();
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         comp->closeOffset();
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });

        Register::addEvent("set_dotted_line", [&](json &param) {
            // 切换器
            //std::cout<<"lt "<<lt<<std::endl;
            std::string type = param["dot_type"];
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     //std::cout<<"lt \n";
                                     comp->setDotLine(type);
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         comp->setDotLine(type);
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });


        Register::addEvent("get_offset", [&](json &param) {
            // 切换器

            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor) {
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     auto ofs = comp->getOffset();
                                     std::string fofs;
                                     if(ofs > 0){
                                         fofs = "open";
                                     }
                                     else {
                                         fofs = "close";
                                     }

                                     param["offset"] = fofs;
                                     param["status"] = SUCCEED;
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors) {
                                     bool matched = false;
                                     json j;
                                     for (auto cursor: cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         auto ofs = comp->getOffset();
                                         std::string fofs;
                                         if(ofs > 0){
                                             fofs = "open";
                                         }
                                         else {
                                             fofs = "close";
                                         }
                                         if (!matched) {
                                             j["offset"] = fofs;
                                             matched = true;
                                         } else { // 多值
                                             json b;
                                             b["offset"] = fofs;
                                             if (j != b) {
                                                 matched = false;
                                                 break;
                                             }
                                         }
                                     }
                                     if (matched) {
                                         param["offset"] = j["offset"];
                                         param["status"] = SUCCEED;
                                     } else param["status"] = MULTIVL;
                                 });
            return param;
        });
    }

    Line::Line() {
        if (!registered) {
            registering(); // 注册
             initArrow();
        }
        addModuleTypes(module_type); // 添加模块类型

    }

    //// 通用虚接口
    // 非构造初始化，初始化组件在(x, y)
    void Line::init() {

        setType("line");
        // 父类初始化
        ComponentRotatable::init();
        ComponentStylized::init();
        // 设置类型

        set_line_type(straightLine);
        // 添加图形SVG
        SVGILine = std::make_shared<Lewzen::SVGIPath>();
        SVGICurve = std::make_shared<Lewzen::SVGIPath>();
        SVGIVerticalLine = std::make_shared<Lewzen::SVGIPath>();
        SVGIHorizontalLine = std::make_shared<Lewzen::SVGIPath>();
        SVGICurveTwo = std::make_shared<Lewzen::SVGIPath>();
        SVGIHallowLine = std::make_shared<Lewzen::SVGIPath>();
        SVGIComplexLine = std::make_shared<Lewzen::SVGIPath>();
        SVGIFlexableLine = std::make_shared<Lewzen::SVGIPath>();

        SVGILineHide = std::make_shared<Lewzen::SVGIPath>();
        SVGICurveHide = std::make_shared<Lewzen::SVGIPath>();
        SVGIVerticalLineHide = std::make_shared<Lewzen::SVGIPath>();
        SVGIHorizontalLineHide = std::make_shared<Lewzen::SVGIPath>();
        SVGICurveTwoHide = std::make_shared<Lewzen::SVGIPath>();
        SVGIHallowLineHide = std::make_shared<Lewzen::SVGIPath>();
        SVGIComplexLineHide = std::make_shared<Lewzen::SVGIPath>();
        SVGIFlexableLineHide = std::make_shared<Lewzen::SVGIPath>();


        // 初始化关键点表
        startPoint = createCorePoint("start", 100, 100);
        endPoint = createCorePoint("end", 200, 200);
        startPoint->setVirtual(0);
        endPoint->setVirtual(0);
        std::string id = "mid";
        midPoint = createCorePoint(id,
                                   (startPoint->getX() + endPoint->getX()) / 2,
                                   (startPoint->getY() + endPoint->getY()) / 2);


        midPoint->setVirtual(0);

        midCPoint = createCorePoint("midC", startPoint->getX(), startPoint->getY());
        arrowPoint = createCorePoint("arrow", startPoint->getX(), startPoint->getY());
        arrowCPoint = createCorePoint("arrowC", startPoint->getX(), startPoint->getY());

        auto mid0 = createCorePoint("0.5",(startPoint->getX() + endPoint->getX()) / 2,
                                    (startPoint->getY() + endPoint->getY()) / 2);
        mid0->setVirtual(1);

        pointList.push_back(startPoint);
        pointList.push_back(mid0);
        pointList.push_back(endPoint);
        // 注册关键点
        setCorePoints(pointList);
        // 默认样式
        setStyle("stroke: black; fill: none; stroke-width: 1px;");
        // 绑定属性
        std::function<std::string()> _getD = std::bind(&Line::getD, this);
        SVGILine->D.bind(_getD);
        SVGILineHide->D.bind(_getD);
        SVGILineHide->Opacity=0;
        SVGILineHide->StrokeWidth=10;
        SVGIG->add(SVGILine);
        SVGIG->add(SVGILineHide);



        std::function<std::string()> _getCurveD = std::bind(&Line::getCurveD, this);
        SVGICurve->D.bind(_getCurveD);
        SVGICurveHide->D.bind(_getCurveD);
        SVGICurveHide->Opacity=0;
        SVGICurveHide->StrokeWidth=10;


        std::function<std::string()> _getVD = std::bind(&Line::getVerticalLineD, this);
        SVGIVerticalLine->D.bind(_getVD);
        SVGIVerticalLineHide->D.bind(_getVD);
        SVGIVerticalLineHide->Opacity=0;
        SVGIVerticalLineHide->StrokeWidth=10;

        std::function<std::string()> _getHD = std::bind(&Line::getHorizontalLineD, this);
        SVGIHorizontalLine->D.bind(_getHD);
        SVGIHorizontalLineHide->D.bind(_getHD);
        SVGIHorizontalLineHide->Opacity=0;
        SVGIHorizontalLineHide->StrokeWidth=10;

        std::function<std::string()> _getCTD = std::bind(&Line::getCurveTwoD, this);
        SVGICurveTwo->D.bind(_getCTD);
        SVGICurveTwoHide->D.bind(_getCTD);

        SVGICurveTwoHide->Opacity=0;
        SVGICurveTwoHide->StrokeWidth=10;

        std::function<std::string()> _getHalD = std::bind(&Line::getHallowLineD, this);
        SVGIHallowLine->D.bind(_getHalD);
        SVGIHallowLineHide->D.bind(_getHalD);

        SVGIHallowLineHide->Opacity=0;
        SVGIHallowLineHide->StrokeWidth=10;

        std::function<std::string()> _getComD = std::bind(&Line::getComplexLineD, this);
        SVGIComplexLine->D.bind(_getComD);
        SVGIComplexLineHide->D.bind(_getComD);
        SVGIComplexLineHide->Opacity=0;
        SVGIComplexLineHide->StrokeWidth=10;

        std::function<std::string()> _getFlD = std::bind(&Line::getFlexableLineD, this);
        SVGIFlexableLine->D.bind(_getFlD);
        SVGIFlexableLineHide->D.bind(_getFlD);
        SVGIFlexableLineHide->Opacity=0;
        SVGIFlexableLineHide->StrokeWidth=10;


        std::function<std::string()> _getEA = [&]() {
            return "url(#" + getEndArrow() + ")";
        };
        std::function<std::string()> _getSA = [&]() {
            return "url(#" + getStartArrow() + ")";
        };

        endArrow = "end_arrow";
        SVGILine->MarkerEnd = "url(#" + endArrow + ")";
        SVGIHallowLine->MarkerEnd = "url(#null)";
        SVGIComplexLine->MarkerEnd = "url(#null)";
        SVGIFlexableLine->MarkerEnd = "url(#null)";
        SVGIHallowLine->MarkerStart = "url(#null)";
        SVGIComplexLine->MarkerStart = "url(#null)";
        SVGIFlexableLine->MarkerStart = "url(#null)";

//        scale(2.0,2.0);
//        flip(0,1,-200);
    }

    // 拷贝
    ComponentAbstract &Line::operator=(const ComponentAbstract &comp) {
        ComponentRotatable::operator=(comp);
        ComponentStylized::operator=(comp);
        auto &p = dynamic_cast<const Line &>(comp);
        setDotLine(p.getDotType());
        std::string type = p.getLineType();
//        std::cout<<"copy linetype\n"<<type<<std::endl;
        if (type == straightLine) {
            // 拷贝父类
            // 拷贝关键点位置
//            setLineType(type);

            setStartArrow(p.startArrow);
            setEndArrow(p.endArrow);
//            *startPoint = *(p.startPoint);
//            *endPoint = *(p.endPoint);
//            std::cout<<"pls "<<pointList.size()<<std::endl;
            for (int i = 0; i < (int) p.pointList.size(); i++) {
                if (pointList.size() <= i) {
                    pointList.push_back(createCorePoint("tmp", 0, 0));
                }
//                std::cout<<pointList[i]->getId()<<" "<<pointList[i]->getX()<<" "<<pointList[i]->getY()<<std::endl;

                *pointList[i] = *(p.pointList[i]);
                if(pointList[i]->getId() == "start"){
                    startPoint = pointList[i];
                }
                if(pointList[i]->getId() == "end"){
                    endPoint = pointList[i];
                }
            }
            setCorePoints(pointList);
            if(p.offset > 0)onOffset();

        } else if (type == curve) {
            setLineType(p.getLineType());
            setStartArrow(p.startArrow);
            setEndArrow(p.endArrow);
            // 拷贝关键点位置
            *startPoint = *(p.startPoint);
            *endPoint = *(p.endPoint);
            *midPoint = *(p.midPoint);

        } else if (type == horizontalLine) {

            setLineType(p.getLineType());
            setStartArrow(p.startArrow);
            setEndArrow(p.endArrow);
            // 拷贝关键点位置
            *startPoint = *(p.startPoint);
            *endPoint = *(p.endPoint);
            *midPoint = *(p.midPoint);

            if(p.offset > 0)onOffset();

        } else if (type == verticalLine) {
            // 拷贝父类

//            std::cout<<"type vecttt\n\n\n";
            setLineType(p.getLineType());
            setStartArrow(p.startArrow);
            setEndArrow(p.endArrow);
            // 拷贝关键点位置
            *startPoint = *(p.startPoint);
            *endPoint = *(p.endPoint);
            *midPoint = *(p.midPoint);

            if(p.offset > 0)onOffset();

        } else if (type == curveTwo) {
            // 拷贝父类

            setLineType(p.getLineType());
            setStartArrow(p.startArrow);
            setEndArrow(p.endArrow);
            // 拷贝关键点位置
            *startPoint = *(p.startPoint);
            *endPoint = *(p.endPoint);
            *midPoint = *(p.midPoint);
            *midCPoint = *(p.midCPoint);



        } else if (type == hallowLine) {

            // 拷贝父类
            setLineType(p.getLineType());
            // 拷贝关键点位置
            *startPoint = *(p.startPoint);
            *endPoint = *(p.endPoint);


        } else if (type == complexLine) {
            setLineType(p.getLineType());


            // 拷贝关键点位置
            *startPoint = *(p.startPoint);
            *endPoint = *(p.endPoint);

            *arrowPoint = *(p.arrowPoint);
            *arrowCPoint = *(p.arrowCPoint);


            *midPoint = *(p.midPoint);
            *midCPoint = *(p.midCPoint);

        }
        else if(type == flexableLine){
            SVGIG->children({});
            set_line_type(type);
            corePoints.clear();
            pointList.clear();

//            *startPoint = *(p.startPoint);
//            *endPoint = *(p.endPoint);
            *arrowPoint = *(p.arrowPoint);
            *arrowCPoint = *(p.arrowCPoint);

            *midPoint = *(p.midPoint);
            *midCPoint = *(p.midCPoint);

            // 拷贝关键点位置
            pointList.clear();
//            corePoints.clear();
//            std::cout<<"pls "<<pointList.size()<<std::endl;
            for (int i = 0; i < (int) p.pointList.size(); i++) {
                if (pointList.size() <= i) {
                    pointList.push_back(createCorePoint("tmp", 0, 0));
                }
                *pointList[i] = *(p.pointList[i]);
                if(pointList[i]->getId() == "start"){
                    startPoint = pointList[i];
                }
                if(pointList[i]->getId() == "end"){
                    endPoint = pointList[i];
                }
            }

            setCorePoints(pointList);
            setCorePoints({midPoint,midCPoint,arrowPoint,arrowCPoint});
            SVGIG->add(SVGIFlexableLine);
            SVGIG->add(SVGIFlexableLineHide);
        }
        return *this;
    }

    // 序列化，并记录已操作的
    void Line::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        ComponentRotatable::serialize(j, processed);
        ComponentStylized::serialize(j, processed);

        j["end_arrow"] = endArrow;
        j["start_arrow"] = startArrow;
        j["line_type"] = getLineType();
        j["offset"] = offset;
        j["dot_type"] = dotType;
        // (无额外私有内容)
    }

    // 反序列化
    ComponentAbstract &Line::operator=(const json &j) {
        // 父类反序列化
        ComponentStylized::operator=(j);
        ComponentRotatable::operator=(j);
        SVGIG->children({});
        pointList.clear();
        set_line_type(j["line_type"]);
        offset = j["offset"];
        setDotLine(j["dot_type"]);
        std::cout<<"fxlh "<<getLineType()<<" "<<startArrow<<" "<<endArrow<<" "<<offset<<std::endl;
        std::string type = getLineType();
        if (type == straightLine) {
            setStartArrow(j["start_arrow"]);
            setEndArrow(j["end_arrow"]);
            // 注册关键点
            startPoint = corePoints["start"];
            endPoint = corePoints["end"];
            std::vector<double>tmp;
            for(auto t:corePoints){
                double val;
                if(t.first == "start")val=0;
                else if(t.first == "end")val = 1;
                else val = std::stod(t.first);
                tmp.push_back(val);

            }

            sort(tmp.begin(),tmp.end());
            for(auto t:tmp){
                std::string val;
                if(t == 0){
                    val = "start";
                }
                else if(t == 1)val = "end";
                else{
                    for(auto p:corePoints){
                        if(p.first=="start"||p.first=="end")continue;
                        auto p1 = std::stod(p.first);
                        if(fabs(p1-t)<1e-7){
                            val = p.first;break;
                        }
                    }
                }

                if(corePoints.count(val)){
                    auto tt = corePoints[val];
                    pointList.push_back(corePoints[val]);
                }
                else{
                    std::cout<<"valdddddd"<<val<<"\n\n\n";
                }

            }
            if(offset>0)onOffset();
            SVGIG->add(SVGILine);
            SVGIG->add(SVGILineHide);

        } else if (type == curve) {
            setStartArrow(j["start_arrow"]);
            setEndArrow(j["end_arrow"]);
            // 注册关键点
            startPoint = corePoints["start"];
            endPoint = corePoints["end"];
            midPoint = corePoints["mid"];
            pointList.push_back(startPoint);
            pointList.push_back(midPoint);
            pointList.push_back(endPoint);


            SVGIG->add(SVGICurve);
            SVGIG->add(SVGICurveHide);
        } else if (type == verticalLine) {
            setStartArrow(j["start_arrow"]);
            setEndArrow(j["end_arrow"]);
            // 注册关键点
            startPoint = corePoints["start"];
            endPoint = corePoints["end"];
            midPoint = corePoints["mid"];
            pointList.push_back(startPoint);
            pointList.push_back(midPoint);
            pointList.push_back(endPoint);
            if(offset>0)onOffset();
            SVGIG->add(SVGIVerticalLine);
            SVGIG->add(SVGIVerticalLineHide);
        } else if (type == horizontalLine) {
            setStartArrow(j["start_arrow"]);
            setEndArrow(j["end_arrow"]);
            // 注册关键点
            startPoint = corePoints["start"];
            endPoint = corePoints["end"];
            midPoint = corePoints["mid"];
            pointList.push_back(startPoint);
            pointList.push_back(midPoint);
            pointList.push_back(endPoint);
            if(offset>0)onOffset();
            SVGIG->add(SVGIHorizontalLine);
            SVGIG->add(SVGIHorizontalLineHide);
        } else if (type == curveTwo) {
            setStartArrow(j["start_arrow"]);
            setEndArrow(j["end_arrow"]);
            startPoint = corePoints["start"];
            endPoint = corePoints["end"];
            midPoint = corePoints["mid"];
            midCPoint = corePoints["midC"];
            pointList.push_back(startPoint);
            pointList.push_back(midPoint);
            pointList.push_back(midCPoint);
            pointList.push_back(endPoint);

            SVGIG->add(SVGICurveTwo);
            SVGIG->add(SVGICurveTwoHide);
        } else if (type == hallowLine) {

            startPoint = corePoints["start"];
            endPoint = corePoints["end"];
            pointList.push_back(startPoint);
            pointList.push_back(endPoint);
            SVGIG->add(SVGIHallowLine);
            SVGIG->add(SVGIHallowLineHide);
        } else if (type == complexLine) {
            startPoint = corePoints["start"];
            endPoint = corePoints["end"];
            midPoint = corePoints["mid"];
            midCPoint = corePoints["midC"];
            arrowPoint = corePoints["arrow"];
            arrowCPoint = corePoints["arrowC"];
            pointList.push_back(startPoint);
            pointList.push_back(arrowCPoint);
            pointList.push_back(arrowPoint);
            pointList.push_back(midPoint);
            pointList.push_back(midCPoint);
            pointList.push_back(endPoint);
            SVGIG->add(SVGIComplexLine);
            SVGIG->add(SVGIComplexLineHide);
        }
        else if(type == flexableLine){
            startPoint = corePoints["start"];
            endPoint = corePoints["end"];
            midPoint = corePoints["mid"];
            midCPoint = corePoints["midC"];
            arrowPoint = corePoints["arrow"];
            arrowCPoint = corePoints["arrowC"];
            std::vector<double>tmp;
            for(auto t:corePoints){
                if(t.first=="mid"||t.first=="midC"||t.first=="arrow"||t.first=="arrowC")continue;
                double val;
                if(t.first == "start")val=0;
                else if(t.first == "end")val = 1;
                else val = std::stod(t.first);
                tmp.push_back(val);
            }
            sort(tmp.begin(),tmp.end());
            for(auto t:tmp){
                std::string val;
                if(t == 0){
                    val = "start";
                }
                else if(t == 1)val = "end";
                else{
                    for(auto p:corePoints){
                        if(p.first=="start"||p.first=="end")continue;
                        if(p.first=="mid"||p.first=="midC"||p.first=="arrow"||p.first=="arrowC")continue;

                        auto p1 = std::stod(p.first);
                        if(fabs(p1-t)<1e-7){
                            val = p.first;break;
                        }
                    }
                }
                if(corePoints.count(val)){
                    auto tt = corePoints[val];
                    pointList.push_back(corePoints[val]);
                }
                else{
                    std::cout<<"valdddddd"<<val<<"\n\n\n";
                }
            }
            SVGIG->add(SVGIFlexableLine);
            SVGIG->add(SVGIFlexableLineHide);
        }
        std::cout<<"kkk\n\n\n";
        return *this;
    }


    //// Basics虚接口
    // 移动关键点
    void Line::moveCorePoint(const std::string &id, const double &_dx, const double &_dy) {
        auto delta = vectorFromCanvas(Lewzen::canvas_point(_dx, _dy)); // 计算组件坐标系的Δ
        double dx = delta.get_x(), dy = delta.get_y();
        std::string type = getLineType();
        if (type == straightLine) {
            int realId = -1;
            for (int i = 0; i < (int) pointList.size(); i++) {
                if (pointList[i]->getId() == id) {
                    realId = i;
                    break;
                }
            }
            if (realId == -1) {
                //std::cout << "id wrong" << std::endl;
                return;
            }
            auto now = pointList[realId];

            if (now->getVirtual() == 0) {
                //不透明关键点

                *now += createPoint(dx, dy);
                if (now->getId() != "start" && now->getId() != "end") {
                    auto nextP = pointList[realId + 2];
                    auto preP = pointList[realId - 2];
                    Lewzen::Point2D a = *preP, b = *now, c = *nextP;
                    if ((b.get_x() - a.get_x()) * (c.get_y() - a.get_y()) -
                        (c.get_x() - a.get_x()) * (b.get_y() - a.get_y()) == 0) {
                        //共线，删除
                        ComponentRotatable::removeCorePoint(pointList[realId + 1]->getId());
                        ComponentRotatable::removeCorePoint(pointList[realId - 1]->getId());

                        pointList.erase(pointList.begin() + realId + 1);
                        pointList.erase(pointList.begin() + realId - 1);
                        now->setVirtual(1);
                    } else {
                        //不共线，修改,透明关键点
                        pointList[realId + 1]->setX((now->getX() + nextP->getX()) / 2);
                        pointList[realId + 1]->setY((now->getY() + nextP->getY()) / 2);

                        pointList[realId - 1]->setX((now->getX() + preP->getX()) / 2);
                        pointList[realId - 1]->setY((now->getY() + preP->getY()) / 2);
                    }
                } else if (now->getId() == "start") {
                    auto nextP = pointList[realId + 2];
                    pointList[realId + 1]->setX((now->getX() + nextP->getX()) / 2);
                    pointList[realId + 1]->setY((now->getY() + nextP->getY()) / 2);
                } else if (now->getId() == "end") {
                    auto preP = pointList[realId - 2];
                    pointList[realId - 1]->setX((now->getX() + preP->getX()) / 2);
                    pointList[realId - 1]->setY((now->getY() + preP->getY()) / 2);
                }
            } else {
                //透明关键点
                *now += createPoint(dx, dy);
                now->setVirtual(0);

                auto nextP = pointList[realId + 1];
                auto preP = pointList[realId - 1];
                double n,nextN,preN;
                if(nextP->getId() == "end"){
                    nextN = 1;
                }
                else{
                    nextN = stod(nextP->getId());
                }
                if(preP->getId() == "start"){
                    preN = 0;
                }
                else{
                    preN = stod(preP->getId());
                }
                n = std::stod(now->getId());
                std::string name1 = std::to_string((n + preN)/2.0);//"mid" + std::to_string(ndSize++);
                std::string name2 = std::to_string((n+nextN)/2.0);//"mid" + std::to_string(ndSize++);

                auto m1 = createCorePoint(name1, (now->getX() + preP->getX()) / 2, (now->getY() + preP->getY()) / 2);
                auto m2 = createCorePoint(name2, (now->getX() + nextP->getX()) / 2, (now->getY() + nextP->getY()) / 2);
                m1->setVirtual(1);
                m2->setVirtual(1);
                setCorePoints({m1, m2});
                pointList.insert(pointList.begin() + realId + 1, m2);
                pointList.insert(pointList.begin() + realId, m1);

            }

            //        setCorePoints(pointList);
            onRotateCenterChanged(); // 旋转中心变化响应
            onChanged(); // 更新事件
        }
        else if (type == curve) {
            if (id == "mid") {
                *midPoint += createPoint(dx, dy);
            } else if (id == "start") {
                *startPoint += createPoint(dx, dy);
            } else if (id == "end") {
                *endPoint += createPoint(dx, dy);
            }

            onRotateCenterChanged(); // 旋转中心变化响应
            onChanged(); // 更新事件
        }
        else if (type == verticalLine) {
            if (id == "mid") {
                *midPoint += createPoint(dx, 0);
            } else if (id == "start") {
                *startPoint += createPoint(dx, dy);
                midPoint->setY((startPoint->getY() + endPoint->getY()) / 2);
            } else if (id == "end") {
                *endPoint += createPoint(dx, dy);
                midPoint->setY((startPoint->getY() + endPoint->getY()) / 2);
            }


            onRotateCenterChanged(); // 旋转中心变化响应
            onChanged(); // 更新事件
        }
        else if (type == horizontalLine) {
            if (id == "mid") {
                *midPoint += createPoint(0, dy);
            } else if (id == "start") {
                *startPoint += createPoint(dx, dy);
                midPoint->setX((startPoint->getX() + endPoint->getX()) / 2);
            } else if (id == "end") {
                *endPoint += createPoint(dx, dy);
                midPoint->setX((startPoint->getX() + endPoint->getX()) / 2);
            }


            onRotateCenterChanged(); // 旋转中心变化响应
            onChanged(); // 更新事件
        }
        else if (type == curveTwo) {
            if (id == "mid") {
                *midPoint += createPoint(dx, dy);
            } else if (id == "start") {
                *startPoint += createPoint(dx, dy);
            } else if (id == "end") {
                *endPoint += createPoint(dx, dy);
            } else if (id == "midC") {
                *midCPoint += createPoint(dx, dy);
            }

            onRotateCenterChanged(); // 旋转中心变化响应
            onChanged(); // 更新事件
        }
        else if (type == hallowLine) {

            if (id == "start") {
                *startPoint += createPoint(dx, dy);
            } else if (id == "end") {
                *endPoint += createPoint(dx, dy);
            }

            onRotateCenterChanged(); // 旋转中心变化响应
            onChanged(); // 更新事件
        }
        else if (type == complexLine) {
            if (id == "start") {
                double ew,eh,eh1,sw,sh,sh1;
                double x1 = startPoint->getX(), y1 = startPoint->getY(), x2 = endPoint->getX(), y2 = endPoint->getY();
                double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                double m = midPoint->getX(), n = midPoint->getY();
                Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                   (a * a * n - a * b * m - b * c) / (a * a + b * b));
                ew = dist2d(cz,Lewzen::Point2D(endPoint->getX(),endPoint->getY()));
                eh = dist2d(cz,Lewzen::Point2D(midPoint->getX(),midPoint->getY()));
                eh1 = dist2d(cz,Lewzen::Point2D(midCPoint->getX(),midCPoint->getY()));

                m = arrowPoint->getX();n = arrowPoint->getY();
                Lewzen::Point2D z((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                  (a * a * n - a * b * m - b * c) / (a * a + b * b));
                sw = dist2d(z,Lewzen::Point2D(startPoint->getX(),startPoint->getY()));
                sh = dist2d(z,Lewzen::Point2D(arrowPoint->getX(),arrowPoint->getY()));
                sh1 = dist2d(z,Lewzen::Point2D(arrowCPoint->getX(),arrowCPoint->getY()));

                *startPoint += createPoint(dx, dy);
                calcComplexPoint(ew,eh,eh1,sw,sh,sh1);

            }
            else if (id == "end") {

                double ew,eh,eh1,sw,sh,sh1;
                double x1 = startPoint->getX(), y1 = startPoint->getY(), x2 = endPoint->getX(), y2 = endPoint->getY();
                double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                double m = midPoint->getX(), n = midPoint->getY();
                Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                   (a * a * n - a * b * m - b * c) / (a * a + b * b));
                ew = dist2d(cz,Lewzen::Point2D(endPoint->getX(),endPoint->getY()));
                eh = dist2d(cz,Lewzen::Point2D(midPoint->getX(),midPoint->getY()));
                eh1 = dist2d(cz,Lewzen::Point2D(midCPoint->getX(),midCPoint->getY()));

                m = arrowPoint->getX();n = arrowPoint->getY();
                Lewzen::Point2D z((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                   (a * a * n - a * b * m - b * c) / (a * a + b * b));
                sw = dist2d(z,Lewzen::Point2D(startPoint->getX(),startPoint->getY()));
                sh = dist2d(z,Lewzen::Point2D(arrowPoint->getX(),arrowPoint->getY()));
                sh1 = dist2d(z,Lewzen::Point2D(arrowCPoint->getX(),arrowCPoint->getY()));

                *endPoint += createPoint(dx, dy);
                calcComplexPoint(ew,eh,eh1,sw,sh,sh1);
            }
            else if (id == "midC") {
                *midCPoint += createPoint(dx, dy);
                double x1 = startPoint->getX(), y1 = startPoint->getY(), x2 = endPoint->getX(), y2 = endPoint->getY();
                double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                double m = midCPoint->getX(), n = midCPoint->getY();
                Lewzen::Point2D tmpMidc(m, n);
                Lewzen::Point2D tmpM(midPoint->getX(), midPoint->getY());
                Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                   (a * a * n - a * b * m - b * c) / (a * a + b * b));

                double lmc = dist2d(cz, tmpMidc);
                double lm = fabs(a*tmpM.get_x()+b*tmpM.get_y()+c)/sqrt(a*a+b*b);
                double rate = lm / lmc;
                double nx = rate * (m - cz.get_x()) + cz.get_x();
                double ny = rate * (n - cz.get_y()) + cz.get_y();
                midPoint->setX(nx);
                midPoint->setY(ny);
            }
            else if (id == "arrowC") {
                *arrowCPoint += createPoint(dx, dy);
                double x1 = startPoint->getX(), y1 = startPoint->getY(), x2 = endPoint->getX(), y2 = endPoint->getY();
                double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                double m = arrowCPoint->getX(), n = arrowCPoint->getY();
                Lewzen::Point2D tmpMidc(m, n);
                Lewzen::Point2D tmpM(arrowPoint->getX(), arrowPoint->getY());
                Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                   (a * a * n - a * b * m - b * c) / (a * a + b * b));
                double lmc = dist2d(cz, tmpMidc);
                double lm = fabs(a*tmpM.get_x()+b*tmpM.get_y()+c)/sqrt(a*a+b*b);
                double rate = lm / lmc;
                double nx = rate * (m - cz.get_x()) + cz.get_x();
                double ny = rate * (n - cz.get_y()) + cz.get_y();
                arrowPoint->setX(nx);
                arrowPoint->setY(ny);
            }
            else if (id == "mid") {
                double m = midPoint->getX(), n = midPoint->getY();
                std::cout<<"before "<<midPoint->getX()<<" "<<midPoint->getY()<<std::endl;
                Lewzen::Point2D tmpM(m, n);
                Lewzen::Point2D tmpMidc(midCPoint->getX(), midCPoint->getY());
                double lm_mc = dist2d(tmpM, tmpMidc);

                *midPoint += createPoint(dx, dy);
                std::cout<<"after "<<midPoint->getX()<<" "<<midPoint->getY()<<std::endl;

                double x1 = startPoint->getX(), y1 = startPoint->getY(), x2 = endPoint->getX(), y2 = endPoint->getY();
                double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                m = midPoint->getX(), n = midPoint->getY();
                Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                   (a * a * n - a * b * m - b * c) / (a * a + b * b));
                double lm_cz = dist2d(Lewzen::Point2D(midPoint->getX(), midPoint->getY()), cz);
                double lmc_cz = lm_mc + lm_cz;
                double rate = lm_mc / lmc_cz;
                double nx = (midPoint->getX() - rate * cz.get_x()) / (1 - rate);
                double ny = (midPoint->getY() - rate * cz.get_y()) / (1 - rate);
                midCPoint->setX(nx);
                midCPoint->setY(ny);
                std::cout<<"after C "<<midCPoint->getX()<<" "<<midCPoint->getY()<<std::endl;

                m = arrowPoint->getX();
                n = arrowPoint->getY();

                Lewzen::Point2D z((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                  (a * a * n - a * b * m - b * c) / (a * a + b * b));
                double la_z = dist2d(Lewzen::Point2D(arrowPoint->getX(), arrowPoint->getY()), z);
                double la_ac = dist2d(Lewzen::Point2D(arrowPoint->getX(), arrowPoint->getY()),
                                      Lewzen::Point2D(arrowCPoint->getX(), arrowCPoint->getY()));

                rate = lm_cz / la_z;
                nx = rate * (arrowPoint->getX() - z.get_x()) + z.get_x();
                ny = rate * (arrowPoint->getY() - z.get_y()) + z.get_y();
                arrowPoint->setX(nx);
                arrowPoint->setY(ny);
                std::cout<<"after a "<<arrowPoint->getX()<<" "<<arrowPoint->getY()<<std::endl;
                double lac_z = la_ac + dist2d(Lewzen::Point2D(arrowPoint->getX(), arrowPoint->getY()), z);
                rate = la_ac / lac_z;
                nx = (arrowPoint->getX() - rate * z.get_x()) / (1 - rate);
                ny = (arrowPoint->getY() - rate * z.get_y()) / (1 - rate);
                arrowCPoint->setX(nx);
                arrowCPoint->setY(ny);
                std::cout<<"after ac "<<arrowCPoint->getX()<<" "<<arrowCPoint->getY()<<std::endl;

            }
            else if (id == "arrow") {
                double m = arrowPoint->getX(), n = arrowPoint->getY();
                Lewzen::Point2D tmpM(m, n);
                Lewzen::Point2D tmpMidc(arrowCPoint->getX(), arrowCPoint->getY());
                double lm_mc = dist2d(tmpM, tmpMidc);

                *arrowPoint += createPoint(dx, dy);

                double x1 = startPoint->getX(), y1 = startPoint->getY(), x2 = endPoint->getX(), y2 = endPoint->getY();
                double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                m = arrowPoint->getX(), n = arrowPoint->getY();
                Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                   (a * a * n - a * b * m - b * c) / (a * a + b * b));
                double lm_cz = dist2d(Lewzen::Point2D(arrowPoint->getX(), arrowPoint->getY()), cz);
                double lmc_cz = lm_mc + lm_cz;
                double rate = lm_mc / lmc_cz;
                double nx = (arrowPoint->getX() - rate * cz.get_x()) / (1 - rate);
                double ny = (arrowPoint->getY() - rate * cz.get_y()) / (1 - rate);
                arrowCPoint->setX(nx);
                arrowCPoint->setY(ny);

                m = midPoint->getX();
                n = midPoint->getY();

                Lewzen::Point2D z((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                  (a * a * n - a * b * m - b * c) / (a * a + b * b));
                double la_z = dist2d(Lewzen::Point2D(midPoint->getX(), midPoint->getY()), z);
                double la_ac = dist2d(Lewzen::Point2D(midPoint->getX(), midPoint->getY()),
                                      Lewzen::Point2D(midCPoint->getX(), midCPoint->getY()));

                rate = lm_cz / la_z;
                nx = rate * (midPoint->getX() - z.get_x()) + z.get_x();
                ny = rate * (midPoint->getY() - z.get_y()) + z.get_y();
                midPoint->setX(nx);
                midPoint->setY(ny);
                double lac_z = la_ac + dist2d(Lewzen::Point2D(midPoint->getX(), midPoint->getY()), z);
                rate = la_ac / lac_z;
                nx = (midPoint->getX() - rate * z.get_x()) / (1 - rate);
                ny = (midPoint->getY() - rate * z.get_y()) / (1 - rate);
                midCPoint->setX(nx);
                midCPoint->setY(ny);
            }

            onRotateCenterChanged(); // 旋转中心变化响应
            onChanged(); // 更新事件
        }
        else if(type == flexableLine){
            if (id == "midC") {
                *midCPoint += createPoint(dx, dy);
                int sz = pointList.size()-1;
                auto s = pointList[sz-2];
                double x1 = s->getX(), y1 = s->getY(), x2 = endPoint->getX(), y2 = endPoint->getY();
                double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                double m = midCPoint->getX(), n = midCPoint->getY();
                Lewzen::Point2D tmpMidc(m, n);
                Lewzen::Point2D tmpM(midPoint->getX(), midPoint->getY());
                Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                   (a * a * n - a * b * m - b * c) / (a * a + b * b));

                double lmc = dist2d(cz, tmpMidc);
                double lm = fabs(a*tmpM.get_x()+b*tmpM.get_y()+c)/sqrt(a*a+b*b);
                double rate = lm / lmc;
                double nx = rate * (m - cz.get_x()) + cz.get_x();
                double ny = rate * (n - cz.get_y()) + cz.get_y();
                midPoint->setX(nx);
                midPoint->setY(ny);
            }
            else if (id == "arrowC") {
                *arrowCPoint += createPoint(dx, dy);
                auto e = pointList[2];
                double x1 = startPoint->getX(), y1 = startPoint->getY(),
                x2 = e->getX(), y2 = e->getY();

                double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                double m = arrowCPoint->getX(), n = arrowCPoint->getY();
                Lewzen::Point2D tmpMidc(m, n);
                Lewzen::Point2D tmpM(arrowPoint->getX(), arrowPoint->getY());
                Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                   (a * a * n - a * b * m - b * c) / (a * a + b * b));
                double lmc = dist2d(cz, tmpMidc);
                double lm = fabs(a*tmpM.get_x()+b*tmpM.get_y()+c)/sqrt(a*a+b*b);
                double rate = lm / lmc;
                double nx = rate * (m - cz.get_x()) + cz.get_x();
                double ny = rate * (n - cz.get_y()) + cz.get_y();
                arrowPoint->setX(nx);
                arrowPoint->setY(ny);
            }
            else if (id == "mid") {
                double m = midPoint->getX(), n = midPoint->getY();
                std::cout<<"before "<<midPoint->getX()<<" "<<midPoint->getY()<<std::endl;
                Lewzen::Point2D tmpM(m, n);
                Lewzen::Point2D tmpMidc(midCPoint->getX(), midCPoint->getY());
                double lm_mc = dist2d(tmpM, tmpMidc);

                *midPoint += createPoint(dx, dy);
                std::cout<<"after "<<midPoint->getX()<<" "<<midPoint->getY()<<std::endl;

                auto startE = pointList[2];
                int sz = pointList.size()-1;
                auto endS = pointList[sz-2];

                double x1 = endS->getX(), y1 = endS->getY(),
                x2 = endPoint->getX(), y2 = endPoint->getY();

                double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                m = midPoint->getX(), n = midPoint->getY();
                Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                   (a * a * n - a * b * m - b * c) / (a * a + b * b));
                double lm_cz = dist2d(Lewzen::Point2D(midPoint->getX(), midPoint->getY()), cz);
                double lmc_cz = lm_mc + lm_cz;
                double rate = lm_mc / lmc_cz;
                double nx = (midPoint->getX() - rate * cz.get_x()) / (1 - rate);
                double ny = (midPoint->getY() - rate * cz.get_y()) / (1 - rate);
                midCPoint->setX(nx);
                midCPoint->setY(ny);
                std::cout<<"after C "<<midCPoint->getX()<<" "<<midCPoint->getY()<<std::endl;

                m = arrowPoint->getX();
                n = arrowPoint->getY();

                x1 = startPoint->getX(), y1 = startPoint->getY(),
                x2 = startE->getX(), y2 = startE->getY();

                a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                Lewzen::Point2D z((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                  (a * a * n - a * b * m - b * c) / (a * a + b * b));
                double la_z = dist2d(Lewzen::Point2D(arrowPoint->getX(), arrowPoint->getY()), z);
                double la_ac = dist2d(Lewzen::Point2D(arrowPoint->getX(), arrowPoint->getY()),
                                      Lewzen::Point2D(arrowCPoint->getX(), arrowCPoint->getY()));

                rate = lm_cz / la_z;
                nx = rate * (arrowPoint->getX() - z.get_x()) + z.get_x();
                ny = rate * (arrowPoint->getY() - z.get_y()) + z.get_y();
                arrowPoint->setX(nx);
                arrowPoint->setY(ny);
                std::cout<<"after a "<<arrowPoint->getX()<<" "<<arrowPoint->getY()<<std::endl;
                double lac_z = la_ac + dist2d(Lewzen::Point2D(arrowPoint->getX(), arrowPoint->getY()), z);
                rate = la_ac / lac_z;
                nx = (arrowPoint->getX() - rate * z.get_x()) / (1 - rate);
                ny = (arrowPoint->getY() - rate * z.get_y()) / (1 - rate);
                arrowCPoint->setX(nx);
                arrowCPoint->setY(ny);
                std::cout<<"after ac "<<arrowCPoint->getX()<<" "<<arrowCPoint->getY()<<std::endl;

            }
            else if (id == "arrow") {
                double m = arrowPoint->getX(), n = arrowPoint->getY();
                Lewzen::Point2D tmpM(m, n);
                Lewzen::Point2D tmpMidc(arrowCPoint->getX(), arrowCPoint->getY());
                double lm_mc = dist2d(tmpM, tmpMidc);

                *arrowPoint += createPoint(dx, dy);

//                double x1 = startPoint->getX(), y1 = startPoint->getY(), x2 = endPoint->getX(), y2 = endPoint->getY();
                auto startE = pointList[2];
                int sz = pointList.size()-1;
                auto endS = pointList[sz-2];

                double x1 = startPoint->getX(), y1 = startPoint->getY(),
                x2 = startE->getX(), y2 = startE->getY();

                double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                m = arrowPoint->getX(), n = arrowPoint->getY();
                Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                   (a * a * n - a * b * m - b * c) / (a * a + b * b));
                double lm_cz = dist2d(Lewzen::Point2D(arrowPoint->getX(), arrowPoint->getY()), cz);
                double lmc_cz = lm_mc + lm_cz;
                double rate = lm_mc / lmc_cz;
                double nx = (arrowPoint->getX() - rate * cz.get_x()) / (1 - rate);
                double ny = (arrowPoint->getY() - rate * cz.get_y()) / (1 - rate);
                arrowCPoint->setX(nx);
                arrowCPoint->setY(ny);

                m = midPoint->getX();
                n = midPoint->getY();
                x1 = endS->getX(), y1 = endS->getY(),
                x2 = endPoint->getX(), y2 = endPoint->getY();
                a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;

                Lewzen::Point2D z((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                  (a * a * n - a * b * m - b * c) / (a * a + b * b));
                double la_z = dist2d(Lewzen::Point2D(midPoint->getX(), midPoint->getY()), z);
                double la_ac = dist2d(Lewzen::Point2D(midPoint->getX(), midPoint->getY()),
                                      Lewzen::Point2D(midCPoint->getX(), midCPoint->getY()));

                rate = lm_cz / la_z;
                nx = rate * (midPoint->getX() - z.get_x()) + z.get_x();
                ny = rate * (midPoint->getY() - z.get_y()) + z.get_y();
                midPoint->setX(nx);
                midPoint->setY(ny);
                double lac_z = la_ac + dist2d(Lewzen::Point2D(midPoint->getX(), midPoint->getY()), z);
                rate = la_ac / lac_z;
                nx = (midPoint->getX() - rate * z.get_x()) / (1 - rate);
                ny = (midPoint->getY() - rate * z.get_y()) / (1 - rate);
                midCPoint->setX(nx);
                midCPoint->setY(ny);
            }
            else {
                double ew,eh,eh1,sw,sh,sh1;
                int sz = pointList.size()-1;

//                auto endPoint = pointList[2];
                auto sP = pointList[sz-2];
                double x1 = sP->getX(), y1 = sP->getY(), x2 = endPoint->getX(), y2 = endPoint->getY();
                double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                double m = midPoint->getX(), n = midPoint->getY();
                Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                   (a * a * n - a * b * m - b * c) / (a * a + b * b));
                ew = dist2d(cz,Lewzen::Point2D(endPoint->getX(),endPoint->getY()));
                eh = dist2d(cz,Lewzen::Point2D(midPoint->getX(),midPoint->getY()));
                eh1 = dist2d(cz,Lewzen::Point2D(midCPoint->getX(),midCPoint->getY()));


                auto eP = pointList[2];
                x1 = startPoint->getX(), y1 = startPoint->getY(),
                x2 = eP->getX(), y2 = eP->getY();
                a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
                m = arrowPoint->getX();n = arrowPoint->getY();
                Lewzen::Point2D z((b * b * m - a * b * n - a * c) / (a * a + b * b),
                                  (a * a * n - a * b * m - b * c) / (a * a + b * b));
                sw = dist2d(z,Lewzen::Point2D(startPoint->getX(),startPoint->getY()));
                sh = dist2d(z,Lewzen::Point2D(arrowPoint->getX(),arrowPoint->getY()));
                sh1 = dist2d(z,Lewzen::Point2D(arrowCPoint->getX(),arrowCPoint->getY()));
                int realId = -1;
                for (int i = 0; i < (int) pointList.size(); i++) {
                    if (pointList[i]->getId() == id) {
                        realId = i;
                        break;
                    }
                }
                if (realId == -1) {
                    //std::cout << "id wrong" << std::endl;
                    return;
                }
                auto now = pointList[realId];

                if (now->getVirtual() == 0) {
                    //不透明关键点

                    *now += createPoint(dx, dy);
                    if (now->getId() != "start" && now->getId() != "end") {
                        auto nextP = pointList[realId + 2];
                        auto preP = pointList[realId - 2];
                        Lewzen::Point2D a = *preP, b = *now, c = *nextP;
                        if ((b.get_x() - a.get_x()) * (c.get_y() - a.get_y()) -
                            (c.get_x() - a.get_x()) * (b.get_y() - a.get_y()) == 0) {
                            //共线，删除
                            ComponentRotatable::removeCorePoint(pointList[realId + 1]->getId());
                            ComponentRotatable::removeCorePoint(pointList[realId - 1]->getId());

                            pointList.erase(pointList.begin() + realId + 1);
                            pointList.erase(pointList.begin() + realId - 1);
                            now->setVirtual(1);
                        } else {
                            //不共线，修改,透明关键点
                            pointList[realId + 1]->setX((now->getX() + nextP->getX()) / 2);
                            pointList[realId + 1]->setY((now->getY() + nextP->getY()) / 2);

                            pointList[realId - 1]->setX((now->getX() + preP->getX()) / 2);
                            pointList[realId - 1]->setY((now->getY() + preP->getY()) / 2);
                        }
                    } else if (now->getId() == "start") {
                        auto nextP = pointList[realId + 2];
                        pointList[realId + 1]->setX((now->getX() + nextP->getX()) / 2);
                        pointList[realId + 1]->setY((now->getY() + nextP->getY()) / 2);
                    } else if (now->getId() == "end") {
                        auto preP = pointList[realId - 2];
                        pointList[realId - 1]->setX((now->getX() + preP->getX()) / 2);
                        pointList[realId - 1]->setY((now->getY() + preP->getY()) / 2);
                    }
                } else {
                    //透明关键点
                    *now += createPoint(dx, dy);
                    now->setVirtual(0);

                    auto nextP = pointList[realId + 1];
                    auto preP = pointList[realId - 1];
                    double n,nextN,preN;
                    if(nextP->getId() == "end"){
                        nextN = 1;
                    }
                    else{
                        nextN = stod(nextP->getId());
                    }
                    if(preP->getId() == "start"){
                        preN = 0;
                    }
                    else{
                        preN = stod(preP->getId());
                    }
                    n = std::stod(now->getId());
                    std::string name1 = std::to_string((n + preN)/2.0);//"mid" + std::to_string(ndSize++);
                    std::string name2 = std::to_string((n+nextN)/2.0);//"mid" + std::to_string(ndSize++);


                    auto m1 = createCorePoint(name1, (now->getX() + preP->getX()) / 2, (now->getY() + preP->getY()) / 2);
                    auto m2 = createCorePoint(name2, (now->getX() + nextP->getX()) / 2, (now->getY() + nextP->getY()) / 2);
                    m1->setVirtual(1);
                    m2->setVirtual(1);
                    setCorePoints({m1, m2});
                    pointList.insert(pointList.begin() + realId + 1, m2);
                    pointList.insert(pointList.begin() + realId, m1);

                }

                calcFlexablePoint(ew,eh,eh1,sw,sh,sh1);
//                std::cout<<"finish\n\n\n\n\n";

            }
            onRotateCenterChanged(); // 旋转中心变化响应
            onChanged(); // 更新事件
        }

    }

    //// Scalable接口
    void Line::scale(const double &scaleX, const double &scaleY) {
        auto lastCenter = getRotateCenter();
        for (auto &p: pointList) {
            p->setY(p->getY() * scaleY);
            p->setX(p->getX() * scaleX);
        }
        onRotateCenterChanged(); // 旋转中心变化响应
        onScaleChanged(lastCenter, scaleX, scaleY); // 大小变化响应
        onChanged(); // 更新事件
    }

    //// Flippable接口
    void Line::flip(const double &a, const double &b, const double &c) {
        auto A = Lewzen::canvas_point(0, 0), B = Lewzen::canvas_point(0, 0);
        auto C = getCenter();
        double theta = 0;
        if (a == 0) {
//            double ly = -c / b; A = Lewzen::canvas_point(0, ly), B = Lewzen::canvas_point(1, ly); theta = 0;
            double ly = -c / b;
            for (auto p: pointList) {
                p->setY(2 * ly - p->getY());
            }
        } else if (b == 0) {
            double lx = -c / a;
//            A = Lewzen::canvas_point(lx, 0), B = Lewzen::canvas_point(lx, 1); theta = ComponentRotatable::PI / 2;
            for (auto p: pointList) {
                p->setX(2 * lx - p->getX());
            }
        } else {
//            double ly = -c / b; double lx = -c / a; A = Lewzen::canvas_point(lx, 0), B = Lewzen::canvas_point(0, ly); theta = std::atan(-b / a);
            for (auto p: pointList) {
                double x0 = p->getX(), y0 = p->getY();
                double ly = (a * b * x0 - a * a * y0 + b * c) / (a * a + b * b), lx = (-b * ly - c) / a;
                p->setX(2 * lx - x0);
                p->setY(2 * ly - y0);
            }
        }
//        auto FlippedC = Lewzen::line_symmetric(C, A, B);
//        // 等价于移动到对称位置然后旋转
//        moveTo(FlippedC.get_x(), FlippedC.get_y());
//        setTheta(theta * 2- getTheta());
        // 响应翻转
        onFlipped(a, b, c);
        onChanged();
    }

    Lewzen::Point2D Line::getRotateCenter() const {
        //std::cout << "rote cent Line\n";
        if (corePoints.size() == 0) return createPoint(0, 0);
        return createPoint((startPoint->getX() + endPoint->getX()) / 2, (startPoint->getY() + endPoint->getY()) / 2);
    }

    //// 线条接口

    void Line::setLineType(std::string lineType) {
//        if (getType() == straightLine) {
//            SVGIG->remove(SVGILine);
//            SVGIG->remove(SVGILineHide);
//        }
//        else if (getType() == curve) {
//            SVGIG->remove(SVGICurve);
//            SVGIG->remove(SVGICurveHide);
//        }
//        else if (getType() == verticalLine) {
//            SVGIG->remove(SVGIVerticalLine);
//            SVGIG->remove(SVGIVerticalLineHide);
//
//        }
//        else if (getType() == horizontalLine) {
//            SVGIG->remove(SVGIHorizontalLine);
//            SVGIG->remove(SVGIHorizontalLineHide);
//        }
//        else if (getType() == curveTwo) {
//            SVGIG->remove(SVGICurveTwo);
//            SVGIG->remove(SVGICurveTwoHide);
//        }
//        else if (getType() == hallowLine) {
//            SVGIG->remove(SVGIHallowLine);
//            SVGIG->remove(SVGIHallowLineHide);
//        }
//        else if (getType() == complexLine) {
//            SVGIG->remove(SVGIComplexLine);
//            SVGIG->remove(SVGIComplexLineHide);
//        }
//        else if(getType() == flexableLine){
//            SVGIG->remove(SVGIFlexableLine);
//            SVGIG->remove(SVGIFlexableLineHide);
//        }
        SVGIG->children({});
        set_line_type(lineType);
        corePoints.clear();
        pointList.clear();

        if (lineType == straightLine) {

            auto mid0 = createCorePoint("0.5",(startPoint->getX() + endPoint->getX()) / 2,
                                        (startPoint->getY() + endPoint->getY()) / 2);
            mid0->setVirtual(1);
            pointList.push_back(startPoint);
            pointList.push_back(mid0);
            pointList.push_back(endPoint);
            setCorePoints(pointList);
            if (endArrow != "null") {
                SVGILine->MarkerEnd = "url(#" + endArrow + ")";
            }
            if (startArrow != "null") {
                SVGILine->MarkerStart = "url(#" + startArrow + ")";
            }
            SVGIG->add(SVGILine);
            SVGIG->add(SVGILineHide);
        } else if (lineType == curve) {
            midPoint->setX(endPoint->getX());
            midPoint->setY(startPoint->getY());
            midPoint->setVirtual(0);
            pointList.push_back(startPoint);
            pointList.push_back(midPoint);
            pointList.push_back(endPoint);
            setCorePoints(pointList);
            if (endArrow != "null") {
                SVGICurve->MarkerEnd = "url(#" + endArrow + ")";
            }
            if (startArrow != "null") {
                SVGICurve->MarkerStart = "url(#" + startArrow + ")";
            }
            SVGIG->add(SVGICurve);
            SVGIG->add(SVGICurveHide);

        } else if (lineType == verticalLine) {
            midPoint->setX((startPoint->getX() + endPoint->getX()) / 2);
            midPoint->setY((startPoint->getY() + endPoint->getY()) / 2);
            midPoint->setVirtual(0);
            pointList.push_back(startPoint);
            pointList.push_back(midPoint);
            pointList.push_back(endPoint);
            setCorePoints(pointList);
            if (endArrow != "null") {
                SVGIVerticalLine->MarkerEnd = "url(#" + endArrow + ")";
            }
            if (startArrow != "null") {
                SVGIVerticalLine->MarkerStart = "url(#" + startArrow + ")";
            }
            SVGIG->add(SVGIVerticalLine);
            SVGIG->add(SVGIVerticalLineHide);
        } else if (lineType == horizontalLine) {
            midPoint->setX((startPoint->getX() + endPoint->getX()) / 2);
            midPoint->setY((startPoint->getY() + endPoint->getY()) / 2);
            midPoint->setVirtual(0);
            pointList.push_back(startPoint);
            pointList.push_back(midPoint);
            pointList.push_back(endPoint);
            setCorePoints(pointList);
            if (endArrow != "null") {
                SVGIHorizontalLine->MarkerEnd = "url(#" + endArrow + ")";
            }
            if (startArrow != "null") {
                SVGIHorizontalLine->MarkerStart = "url(#" + startArrow + ")";
            }
            SVGIG->add(SVGIHorizontalLine);
            SVGIG->add(SVGIHorizontalLineHide);
        } else if (lineType == curveTwo) {
            midPoint->setX(startPoint->getX());
            midPoint->setY((startPoint->getY() + endPoint->getY()) / 2);

            midCPoint->setX(endPoint->getX());
            midCPoint->setY((startPoint->getY() + endPoint->getY()) / 2);

            midPoint->setVirtual(0);
            midCPoint->setVirtual(0);
            pointList.push_back(startPoint);
            pointList.push_back(midPoint);
            pointList.push_back(midCPoint);
            pointList.push_back(endPoint);
            setCorePoints(pointList);
            if (endArrow != "null") {
                SVGICurveTwo->MarkerEnd = "url(#" + endArrow + ")";
            }
            if (startArrow != "null") {
                SVGICurveTwo->MarkerStart = "url(#" + startArrow + ")";
            }
            SVGIG->add(SVGICurveTwo);
            SVGIG->add(SVGICurveTwoHide);
        } else if (lineType == hallowLine) {
            pointList.push_back(startPoint);
            pointList.push_back(endPoint);
            setCorePoints(pointList);
            SVGIG->add(SVGIHallowLine);
            SVGIG->add(SVGIHallowLineHide);
        } else if (lineType == complexLine) {
            calcComplexPoint(30,6,12,30,6,12);
            midPoint->setVirtual(0);
            midCPoint->setVirtual(0);
            arrowPoint->setVirtual(0);
            arrowCPoint->setVirtual(0);

            pointList.push_back(startPoint);
            pointList.push_back(arrowCPoint);
            pointList.push_back(arrowPoint);
            pointList.push_back(midPoint);
            pointList.push_back(midCPoint);
            pointList.push_back(endPoint);
            setCorePoints(pointList);
            SVGIG->add(SVGIComplexLine);
            SVGIG->add(SVGIComplexLineHide);
        }
        else if(lineType == flexableLine){
            calcComplexPoint(30,6,12,30,6,12);
            auto mid0 = createCorePoint("0.5",(startPoint->getX() + endPoint->getX()) / 2,
                                        (startPoint->getY() + endPoint->getY()) / 2);
            midPoint->setVirtual(0);
            midCPoint->setVirtual(0);
            arrowPoint->setVirtual(0);
            arrowCPoint->setVirtual(0);
            mid0->setVirtual(1);

            pointList.push_back(startPoint);
            pointList.push_back(mid0);
            pointList.push_back(endPoint);

            setCorePoints(pointList);
            setCorePoints({midPoint,midCPoint,arrowPoint,arrowCPoint});
            SVGIG->add(SVGIFlexableLine);
            SVGIG->add(SVGIFlexableLineHide);
        }
        onChanged();
    }


    const CorePoint &Line::getStartPoint() const {
        return *startPoint;
    }

    void Line::setStartPoint(const CorePoint &start) {
        *startPoint = start;
    }

    const CorePoint &Line::getEndPoint() const {
        return *endPoint;
    }

    void Line::setEndPoint(const CorePoint &end) {
        *endPoint = end;
    }

    const std::string &Line::getStartArrow() const {
        return startArrow;
    }

    void Line::setStartArrow(const std::string &startArrow) {
//        if(!arrows.count(startArrow))return;
        Line::startArrow = startArrow;
        std::string type = getLineType();
        if (type == straightLine) {
            SVGILine->MarkerStart = "url(#" + startArrow + ")";
        } else if (type == curve) {
            SVGICurve->MarkerStart = "url(#" + startArrow + ")";
        } else if (type == verticalLine) {
            SVGIVerticalLine->MarkerStart = "url(#" + startArrow + ")";
        } else if (type == horizontalLine) {
            SVGIHorizontalLine->MarkerStart = "url(#" + startArrow + ")";
        } else if (type == curveTwo) {
            SVGICurveTwo->MarkerStart = "url(#" + startArrow + ")";
        }
        onChanged();

    }

    const std::string &Line::getEndArrow() const {
        return endArrow;
    }

    void Line::setEndArrow(const std::string &endArrow) {
//        if(!arrows.count(endArrow))return;
//        std::cout << "endArrow\n";
        Line::endArrow = endArrow;

        std::string type = getLineType();
        if (type == straightLine) {
            SVGILine->MarkerEnd = "url(#" + endArrow + ")";
        } else if (type == curve) {
            SVGICurve->MarkerEnd = "url(#" + endArrow + ")";
        } else if (type == verticalLine) {
            SVGIVerticalLine->MarkerEnd = "url(#" + endArrow + ")";
        } else if (type == horizontalLine) {
            SVGIHorizontalLine->MarkerEnd = "url(#" + endArrow + ")";
        } else if (type == curveTwo) {
            SVGICurveTwo->MarkerEnd = "url(#" + endArrow + ")";
        }
        onChanged();
    }

    std::string Line::getD() {
        if (offset == 0) {
            std::string res = "M " + std::to_string(startPoint->getX()) + " "
                              + std::to_string(startPoint->getY()) + " ";

            for (int i = 2; i < (int) pointList.size(); i += 2) {
                res += "L " + std::to_string(pointList[i]->getX()) + " " + std::to_string(pointList[i]->getY()) + " ";
            }
            return res;
        } else {
            std::vector<Lewzen::Point2D> coords;
            for (int i = 0; i < (int) pointList.size(); i += 2) {
                coords.push_back(Lewzen::Point2D(pointList[i]->getX(), pointList[i]->getY()));
            }

            std::vector<Lewzen::Point2D> path = offsetCoords(coords, offset);
            std::string res = "M " + std::to_string(path[0].get_x()) + " "
                              + std::to_string(path[0].get_y()) + " ";
            for (int i = 1; i < (int) path.size(); i += 1) {
                res += "L " + std::to_string(path[i].get_x()) + " " + std::to_string(path[i].get_y()) + " ";
            }

            path = offsetCoords(coords, -offset);
            res += "M " + std::to_string(path[0].get_x()) + " "
                   + std::to_string(path[0].get_y()) + " ";
            for (int i = 1; i < (int) path.size(); i += 1) {
                res += "L " + std::to_string(path[i].get_x()) + " " + std::to_string(path[i].get_y()) + " ";
            }
            return res;
        }

    }

    std::string Line::getCurveD() {
        std::string res = "M " + std::to_string(startPoint->getX()) + " " + std::to_string(startPoint->getY())
                          + " Q " + std::to_string(midPoint->getX()) + " " + std::to_string(midPoint->getY()) +
                          " " + std::to_string(endPoint->getX()) + " " + std::to_string(endPoint->getY());
        return res;
    }

    std::string Line::getVerticalLineD() {
        if (offset == 0) {
            std::string res = "M " + std::to_string(startPoint->getX()) + " " + std::to_string(startPoint->getY())
                              + " L " + std::to_string(midPoint->getX()) + " " + std::to_string(startPoint->getY()) +
                              " L " + std::to_string(midPoint->getX()) + " " + std::to_string(endPoint->getY())
                              + " L " + std::to_string(endPoint->getX()) + " " + std::to_string(endPoint->getY());
            return res;
        } else {
            std::vector<Lewzen::Point2D> coords;
            coords.push_back(Lewzen::Point2D(startPoint->getX(), startPoint->getY()));
            coords.push_back(Lewzen::Point2D(midPoint->getX(), startPoint->getY()));
            coords.push_back(Lewzen::Point2D(midPoint->getX(), endPoint->getY()));
            coords.push_back(Lewzen::Point2D(endPoint->getX(), endPoint->getY()));

            std::vector<Lewzen::Point2D> path = offsetCoords(coords, offset);
            std::string res = "M " + std::to_string(path[0].get_x()) + " "
                              + std::to_string(path[0].get_y()) + " ";
            for (int i = 1; i < (int) path.size(); i++) {
                res += "L " + std::to_string(path[i].get_x()) + " " + std::to_string(path[i].get_y()) + " ";
            }

            path = offsetCoords(coords, -offset);
            res += "M " + std::to_string(path[0].get_x()) + " "
                   + std::to_string(path[0].get_y()) + " ";
            for (int i = 1; i < (int) path.size(); i++) {
                res += "L " + std::to_string(path[i].get_x()) + " " + std::to_string(path[i].get_y()) + " ";
            }
            return res;
        }

    }

    std::string Line::getHorizontalLineD() {
        if (offset == 0) {
            std::string res = "M " + std::to_string(startPoint->getX()) + " " + std::to_string(startPoint->getY())
                              + " L " + std::to_string(startPoint->getX()) + " " + std::to_string(midPoint->getY()) +
                              " L " + std::to_string(endPoint->getX()) + " " + std::to_string(midPoint->getY())
                              + " L " + std::to_string(endPoint->getX()) + " " + std::to_string(endPoint->getY());
            return res;
        } else {
            std::vector<Lewzen::Point2D> coords;
            coords.push_back(Lewzen::Point2D(startPoint->getX(), startPoint->getY()));

            coords.push_back(Lewzen::Point2D(startPoint->getX(), midPoint->getY()));
            coords.push_back(Lewzen::Point2D(endPoint->getX(), midPoint->getY()));
            coords.push_back(Lewzen::Point2D(endPoint->getX(), endPoint->getY()));
            std::vector<Lewzen::Point2D> path = offsetCoords(coords, offset);
            std::string res = "M " + std::to_string(path[0].get_x()) + " "
                              + std::to_string(path[0].get_y()) + " ";
            for (int i = 1; i < (int) path.size(); i++) {
                res += "L " + std::to_string(path[i].get_x()) + " " + std::to_string(path[i].get_y()) + " ";
            }

            path = offsetCoords(coords, -offset);
            res += "M " + std::to_string(path[0].get_x()) + " "
                   + std::to_string(path[0].get_y()) + " ";
            for (int i = 1; i < (int) path.size(); i++) {
                res += "L " + std::to_string(path[i].get_x()) + " " + std::to_string(path[i].get_y()) + " ";
            }
            return res;
        }

    }

    std::string Line::getCurveTwoD() {
        std::string res = "M " + std::to_string(startPoint->getX()) + " " + std::to_string(startPoint->getY())
                          + " C " + std::to_string(midPoint->getX()) + " " + std::to_string(midPoint->getY()) +
                          " " + std::to_string(midCPoint->getX()) + " " + std::to_string(midCPoint->getY())
                          + " " + std::to_string(endPoint->getX()) + " " + std::to_string(endPoint->getY());
        return res;
    }

    std::string Line::getHallowLineD() {
        std::vector<Lewzen::Point2D> res;
        for (int i = 0; i < 7; i++) {
            res.push_back(Lewzen::Point2D(0, 0));
        }
        double arrowLength = 30;
        std::vector<Lewzen::Point2D> coords;
        coords.push_back(Lewzen::Point2D(startPoint->getX(), startPoint->getY()));
        coords.push_back(Lewzen::Point2D(endPoint->getX(), endPoint->getY()));
        res[3] = coords[1];
        std::vector<Lewzen::Point2D> path = offsetCoords(coords, 6);
        res[0] = path[0];

        path = offsetCoords(coords, -6);
        res[6] = path[0];

        double rate = arrowLength / dist2d(coords[0], coords[1]);
        Lewzen::Point2D tmp((coords[0].get_x() - coords[1].get_x()) * rate + coords[1].get_x(),
                            (coords[0].get_y() - coords[1].get_y()) * rate + coords[1].get_y());

        coords[0] = tmp;

        path = offsetCoords(coords, 6);
        res[1] = path[0];

        path = offsetCoords(coords, -6);
        res[5] = path[0];

        path = offsetCoords(coords, 12);
        res[2] = path[0];
        path = offsetCoords(coords, -12);
        res[4] = path[0];

        std::string d = "M " + std::to_string(res[0].get_x()) + " "
                        + std::to_string(res[0].get_y()) + " ";
        for (int i = 1; i < (int) res.size(); i++) {
            d += "L " + std::to_string(res[i].get_x()) + " " + std::to_string(res[i].get_y()) + " ";
        }
        d += "z";
        return d;
    }

    std::string Line::getComplexLineD() {
        std::string res = "M " + std::to_string(startPoint->getX()) + " " + std::to_string(startPoint->getY());
        int sz = pointList.size() - 1;
        for (int i = 1; i <= sz; i++) {
            res += " L " + std::to_string(pointList[i]->getX()) + " " + std::to_string(pointList[i]->getY());
        }
        for (int i = sz - 1; i >= 1; i--) {
            auto t = getFlipPoint(Lewzen::Point2D(pointList[i]->getX(), pointList[i]->getY()));
            res += " L " + std::to_string(t.get_x()) + " " + std::to_string(t.get_y());
        }
        res += "z";
        return res;
    }

    std::string Line::getFlexableLineD() {
        std::stringstream ss;
        auto s = createPoint(startPoint->getX(),startPoint->getY());
        auto e = createPoint(pointList[2]->getX(),pointList[2]->getY());

        auto fa = getFlipP(createPoint(arrowPoint->getX(),arrowPoint->getY()),
                           s,e);
        auto fac = getFlipP(createPoint(arrowCPoint->getX(),arrowCPoint->getY()),s,e);

        ss<<"M "<< arrowPoint->getX()<<" "<<arrowPoint->getY()<<" ";
        ss<<"L "<<arrowCPoint->getX()<<" "<<arrowCPoint->getY()<<" ";
        ss<<"L "<<startPoint->getX()<<" "<<startPoint->getY()<<" ";

        ss<<"L "<<fac.get_x()<<" "<<fac.get_y()<<" ";
        ss<<"L "<<fa.get_x()<<" "<<fa.get_y()<<" ";
        int sz = pointList.size()-1;
        auto s1 = createPoint(pointList[sz-2]->getX(),pointList[sz-2]->getY());
        auto e1 = createPoint(endPoint->getX(),endPoint->getY());
        auto fm = getFlipP(createPoint(midPoint->getX(),midPoint->getY()),
                      s1,e1);
        auto fmc = getFlipP(createPoint(midCPoint->getX(),midCPoint->getY()),s1,e1);

        ss<<"M "<<midPoint->getX()<<" "<<midPoint->getY()<<" ";
        ss<<"L "<<midCPoint->getX()<<" "<<midCPoint->getY()<<" ";
        ss<<"L "<<endPoint->getX()<<" "<<endPoint->getY()<<" ";

        ss<<"L "<<fmc.get_x()<<" "<<fmc.get_y()<<" ";
        ss<<"L "<<fm.get_x()<<" "<<fm.get_y()<<" ";

        std::vector<Lewzen::Point2D>coords;

        coords.push_back(Lewzen::Point2D((arrowPoint->getX()+fa.get_x())/2,(arrowPoint->getY()+fa.get_y())/2));

        for(int i = 2;i<sz;i+=2){
            coords.push_back(Lewzen::Point2D(pointList[i]->getX(),pointList[i]->getY()));
        }
        double len = dist2d(createPoint((arrowPoint->getX()+fa.get_x())/2,(arrowPoint->getY()+fa.get_y())/2),fa);

        coords.push_back(Lewzen::Point2D((midPoint->getX()+fm.get_x())/2,(midPoint->getY()+fm.get_y())/2));


        auto path = offsetCoords(coords,len);
        ss<<"M "<<path[0].get_x()<<" "<<path[0].get_y()<<" ";
        for(int i=1;i<(int)path.size();i++){
            ss<<"L "<<path[i].get_x()<<" "<<path[i].get_y()<<" ";

        }
        path = offsetCoords(coords,-len);

        ss<<"M "<<path[0].get_x()<<" "<<path[0].get_y()<<" ";
        for(int i=1;i<(int)path.size();i++){
            ss<<"L "<<path[i].get_x()<<" "<<path[i].get_y()<<" ";
        }
        return ss.str();

    }

    Lewzen::Point2D Line::getFlipP(Lewzen::Point2D p, Lewzen::Point2D s, Lewzen::Point2D e) {
        double x1 = s.get_x(), y1 = s.get_y(), x2 = e.get_x(), y2 = e.get_y();
        double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
        double m = p.get_x(), n = p.get_y();
        Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                           (a * a * n - a * b * m - b * c) / (a * a + b * b));
        return Lewzen::Point2D(2 * cz.get_x() - p.get_x(), 2 * cz.get_y() - p.get_y());
    }

    Lewzen::Point2D Line::getFlipPoint(Lewzen::Point2D p) {
        double x1 = startPoint->getX(), y1 = startPoint->getY(), x2 = endPoint->getX(), y2 = endPoint->getY();
        double a = y2 - y1, b = x1 - x2, c = x2 * y1 - x1 * y2;
        double m = p.get_x(), n = p.get_y();
        Lewzen::Point2D cz((b * b * m - a * b * n - a * c) / (a * a + b * b),
                           (a * a * n - a * b * m - b * c) / (a * a + b * b));
        return Lewzen::Point2D(2 * cz.get_x() - p.get_x(), 2 * cz.get_y() - p.get_y());
    }

    void Line::calcComplexPoint(double ew, double eh, double eh1, double sw, double sh, double sh1) {

        std::vector<Lewzen::Point2D> coords;
        coords.push_back(Lewzen::Point2D(startPoint->getX(), startPoint->getY()));
        coords.push_back(Lewzen::Point2D(endPoint->getX(), endPoint->getY()));
        double rate = ew / dist2d(coords[0], coords[1]);
        Lewzen::Point2D tmp((coords[0].get_x() - coords[1].get_x()) * rate + coords[1].get_x(),
                            (coords[0].get_y() - coords[1].get_y()) * rate + coords[1].get_y());
        coords[0] = tmp;
        std::vector<Lewzen::Point2D> path = offsetCoords(coords, eh);
        midPoint->setX(path[0].get_x());
        midPoint->setY(path[0].get_y());
        path = offsetCoords(coords, eh1);
        midCPoint->setX(path[0].get_x());
        midCPoint->setY(path[0].get_y());


        coords[0].set_x(startPoint->getX());
        coords[0].set_y(startPoint->getY());
        rate = sw / dist2d(coords[0],coords[1]);
        Lewzen::Point2D tmp1((coords[1].get_x() - coords[0].get_x()) * rate + coords[0].get_x(),
                             (coords[1].get_y() - coords[0].get_y()) * rate + coords[0].get_y());

        coords[1] = tmp1;

        path = offsetCoords(coords, sh);
        arrowPoint->setX(path[1].get_x());
        arrowPoint->setY(path[1].get_y());
        path = offsetCoords(coords, sh1);
        arrowCPoint->setX(path[1].get_x());
        arrowCPoint->setY(path[1].get_y());

        onSameSide();

    }


    void Line::calcFlexablePoint(double ew, double eh, double eh1, double sw, double sh, double sh1) {
        std::vector<Lewzen::Point2D> coords;
        int sz = pointList.size()-1;
        auto sP = pointList[sz-2];
        coords.push_back(Lewzen::Point2D(sP->getX(), sP->getY()));
        coords.push_back(Lewzen::Point2D(endPoint->getX(), endPoint->getY()));
        double rate = ew / dist2d(coords[0], coords[1]);
        Lewzen::Point2D tmp((coords[0].get_x() - coords[1].get_x()) * rate + coords[1].get_x(),
                            (coords[0].get_y() - coords[1].get_y()) * rate + coords[1].get_y());
        coords[0] = tmp;
        std::vector<Lewzen::Point2D> path = offsetCoords(coords, eh);
        midPoint->setX(path[0].get_x());
        midPoint->setY(path[0].get_y());
        path = offsetCoords(coords, eh1);
        midCPoint->setX(path[0].get_x());
        midCPoint->setY(path[0].get_y());

        auto eP = pointList[2];

        coords[0].set_x(startPoint->getX());
        coords[0].set_y(startPoint->getY());
        coords[1].set_x(eP->getX());
        coords[1].set_y(eP->getY());

        rate = sw / dist2d(coords[0],coords[1]);
        Lewzen::Point2D tmp1((coords[1].get_x() - coords[0].get_x()) * rate + coords[0].get_x(),
                             (coords[1].get_y() - coords[0].get_y()) * rate + coords[0].get_y());

        coords[1] = tmp1;

        path = offsetCoords(coords, sh);
        arrowPoint->setX(path[1].get_x());
        arrowPoint->setY(path[1].get_y());
        path = offsetCoords(coords, sh1);
        arrowCPoint->setX(path[1].get_x());
        arrowCPoint->setY(path[1].get_y());

        onSameSideF();

    }

    void Line::onOffset() {
        offset = 4;
        std::string tmp = "null";
        setStartArrow(tmp);
        setEndArrow(tmp);
        onChanged();
    }

    void Line::closeOffset(){
        offset = 0;
        onChanged();
    };

    std::vector<Lewzen::Point2D> Line::offsetCoords(std::vector<Lewzen::Point2D> coords, double offset) {
        std::vector<Lewzen::Point2D> path;
        int N = coords.size() - 1;
        int max = N;
        double mi, mi1, li, li1, ri, ri1, si, si1, Xi1, Yi1;
        Lewzen::Point2D p0(0, 0), p1(0, 0), p2(0, 0);
        int isClosed = (coords[0].get_x() == coords[N].get_x() &&
                        coords[0].get_y() == coords[N].get_y());


        if (!isClosed) {
            p0 = coords[0];
            p1 = coords[1];
            p2 = Lewzen::Point2D(p0.get_x() + (p1.get_y() - p0.get_y()) / dist2d(p0, p1) * offset,
                                 p0.get_y() - (p1.get_x() - p0.get_x()) / dist2d(p0, p1) * offset);

            path.push_back(p2);
            coords.push_back(coords[N]);
            N++;
            max--;
        }
        for (int i = 0; i < max; i++) {
            p0 = coords[i];
            p1 = coords[(i + 1) % N];
            p2 = coords[(i + 2) % N];
            if(p1.get_x() == p0.get_x()){
                mi = 1e9;
            }
            else {
                mi = (p1.get_y() - p0.get_y()) / (p1.get_x() - p0.get_x());
            }
            if(p2.get_x() == p1.get_x()){
                mi1 = 1e9;

            }
            else{
                mi1 = (p2.get_y() - p1.get_y()) / (p2.get_x() - p1.get_x());
            }

            // Prevent alignements
            if (fabs(mi - mi1) > 1e-10) {
//            li = Math.sqrt((p1[0] - p0[0])*(p1[0] - p0[0])+(p1[1] - p0[1])*(p1[1] - p0[1]));
//            li1 = Math.sqrt((p2[0] - p1[0])*(p2[0] - p1[0])+(p2[1] - p1[1])*(p2[1] - p1[1]));
                li = dist2d(p1, p0);
                li1 = dist2d(p2, p1);
                ri = p0.get_x() + offset * (p1.get_y() - p0.get_y()) / li;
                ri1 = p1.get_x() + offset * (p2.get_y() - p1.get_y()) / li1;
                si = p0.get_y() - offset * (p1.get_x() - p0.get_x()) / li;
                si1 = p1.get_y() - offset * (p2.get_x() - p1.get_x()) / li1;
                Xi1 = (mi1 * ri1 - mi * ri + si - si1) / (mi1 - mi);
                Yi1 = (mi * mi1 * (ri1 - ri) + mi1 * si - mi * si1) / (mi1 - mi);
                // Correction for vertical lines
                if (p1.get_x() - p0.get_x() == 0) {
                    if(p1.get_y() - p0.get_y() == 0){
                        Xi1 = p1.get_x();
                    }
                    else{
                        Xi1 = p1.get_x() + offset * (p1.get_y() - p0.get_y()) / fabs(p1.get_y() - p0.get_y());
                    }

                    Yi1 = mi1 * Xi1 - mi1 * ri1 + si1;
                }
                if (p2.get_x() - p1.get_x() == 0) {
                    if(p2.get_y() - p1.get_y() == 0){
                        Xi1 = p2.get_x();
                    }
                    else{
                        Xi1 = p2.get_x() + offset * (p2.get_y() - p1.get_y()) / fabs(p2.get_y() - p1.get_y());
                    }

                    Yi1 = mi * Xi1 - mi * ri + si;
                }
                path.push_back(Lewzen::Point2D(Xi1, Yi1));
            }
        }
        if (isClosed) {
            path.push_back(path[0]);
        } else {
            coords.pop_back();
            p0 = coords[coords.size() - 1];
            p1 = coords[coords.size() - 2];
            p2 = Lewzen::Point2D(p0.get_x() - (p1.get_y() - p0.get_y()) / dist2d(p0, p1) * offset,
                                 p0.get_y() + (p1.get_x() - p0.get_x()) / dist2d(p0, p1) * offset);
            path.push_back(p2);
        }
        return path;
    }

    double Line::dist2d(Lewzen::Point2D coord1, Lewzen::Point2D coord2) {
        double dx = coord2.get_x() - coord1.get_x();
        double dy = coord2.get_y() - coord1.get_y();
        return sqrt(dx * dx + dy * dy);
    }

    void Line::setDotLine(std::string _dotType) {
        dotType = _dotType;
        std::vector<int> tmp{0,0};
        if (dotType == "dashed") {
            tmp = {1, 4};
        } else if (dotType == "dotted") {
            tmp = {1, 1};
        }
        SVGIG->StrokeDasharray = tmp;
        onChanged();
    }

    void Line::onSameSide() {
        double x1 = startPoint->getX(), y1 = startPoint->getY(), x2 = endPoint->getX(), y2 = endPoint->getY();
        double x0 = arrowCPoint->getX(),y0 = arrowCPoint->getY();
        double x3 = midCPoint->getX(),y3 = midCPoint->getY();
        if(((x2-x1)*(y0-y1)-(y2-y1)*(x0-x1)) * ((x2-x1)*(y3-y1)-(y2-y1)*(x3-x1)) < 0) {
            auto t = getFlipPoint(Lewzen::Point2D(x0,y0));
            arrowCPoint->setX(t.get_x());
            arrowCPoint->setY(t.get_y());
            t = getFlipPoint(Lewzen::Point2D(arrowPoint->getX(),arrowPoint->getY()));
            arrowPoint->setX(t.get_x());
            arrowPoint->setY(t.get_y());

        }

    }

    void Line::onSameSideF() {
        auto s = Lewzen::Point2D(startPoint->getX(),startPoint->getY());

        auto e = Lewzen::Point2D(pointList[2]->getX(),pointList[2]->getY());

        int sz = pointList.size()-1;
        auto s1 = Lewzen::Point2D(pointList[sz-2]->getX(),pointList[sz-2]->getY());
        auto e1 = Lewzen::Point2D(endPoint->getX(),endPoint->getY());

        double x1 = s.get_x(), y1 = s.get_y(), x2 = e.get_x(), y2 = e.get_y();
        double x0 = arrowCPoint->getX(),y0 = arrowCPoint->getY();
        double flagS = (x2-x1)*(y0-y1)-(y2-y1)*(x0-x1);

        x1 = s1.get_x();
        y1 = s1.get_y();
        x2 = e1.get_x();
        y2 = e1.get_y();
        x0 = midCPoint->getX();
        y0 = midCPoint->getY();
        double flagE = (x2-x1)*(y0-y1)-(y2-y1)*(x0-x1);
        if(flagS*flagE < 0){
            auto t = getFlipP(Lewzen::Point2D(arrowPoint->getX(),arrowPoint->getY()),s,e);
            arrowPoint->setX(t.get_x());
            arrowPoint->setY(t.get_y());

            t = getFlipP(Lewzen::Point2D(arrowCPoint->getX(),arrowCPoint->getY()),s,e);
            arrowCPoint->setX(t.get_x());
            arrowCPoint->setY(t.get_y());
        }

    }

    void Line::initArrow() {
        end_arrow = std::make_shared<Lewzen::SVGIMarker>();
        end_arrow->Id = "end_arrow";
        end_arrow->MarkerHeight = 13;
        end_arrow->MarkerWidth = 13;
        end_arrow->RefX = 12;
        end_arrow->RefY = 6;
        end_arrow->Orient = "auto";
        end_arrow->MarkerUnits = "userSpaceOnUse";
        arrowPath = std::make_shared<Lewzen::SVGIPath>();
        arrowPath->D = "M0,0 L12,6 L0,12 L4,6 L0,0";
        arrowPath->Fill = "black";
        end_arrow->add(arrowPath);


        start_arrow = std::make_shared<Lewzen::SVGIMarker>();
        start_arrow->Id = "start_arrow";
        start_arrow->MarkerHeight = 13;
        start_arrow->MarkerWidth = 13;
        start_arrow->RefX = 0;
        start_arrow->RefY = 6;
        start_arrow->Orient = "auto";
        start_arrow->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> enda = std::make_shared<Lewzen::SVGIPath>();
        enda->D = "M8,6 L12,0 L0,6 L12,12 L8,6";
        enda->Fill = "black";
        start_arrow->add(enda);


        start_arrow_circle = std::make_shared<Lewzen::SVGIMarker>();
        std::shared_ptr<Lewzen::SVGICircle> t = std::make_shared<Lewzen::SVGICircle>();
        start_arrow_circle->Id = "start_arrow_circle";
        start_arrow_circle->MarkerHeight = 13;
        start_arrow_circle->MarkerWidth = 13;
        start_arrow_circle->RefX = 0;
        start_arrow_circle->RefY = 6;
        start_arrow_circle->Orient = "auto";
        start_arrow_circle->MarkerUnits = "userSpaceOnUse";
        t->Cx = 4;
        t->Cy = 6;
        t->R = 4;
        t->Fill = "black";
        start_arrow_circle->add(t);

        end_arrow_circle = std::make_shared<Lewzen::SVGIMarker>();
        end_arrow_circle->Id = "end_arrow_circle";
        end_arrow_circle->MarkerHeight = 13;
        end_arrow_circle->MarkerWidth = 13;
        end_arrow_circle->RefX = 8;
        end_arrow_circle->RefY = 6;
        end_arrow_circle->Orient = "auto";
        end_arrow_circle->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGICircle> t1 = std::make_shared<Lewzen::SVGICircle>();
        t1->Cx = 4;
        t1->Cy = 6;
        t1->R = 4;
        t1->Fill = "black";
        end_arrow_circle->add(t1);




        arrows["end_arrow"] = end_arrow;
        arrows["start_arrow"] = start_arrow;
        arrows["start_arrow_circle"] = start_arrow_circle;
        arrows["end_arrow_circle"] = end_arrow_circle;

        Defs.push_back(end_arrow);
        Defs.push_back(start_arrow_circle);
        Defs.push_back(end_arrow_circle);
        Defs.push_back(start_arrow);

        end_arrow_tri = std::make_shared<Lewzen::SVGIMarker>();
        end_arrow_tri->Id = "end_arrow_tri";
        end_arrow_tri->MarkerHeight = 13;
        end_arrow_tri->MarkerWidth = 13;
        end_arrow_tri->RefX = 12;
        end_arrow_tri->RefY = 6;
        end_arrow_tri->Orient = "auto";
        end_arrow_tri->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> enda1 = std::make_shared<Lewzen::SVGIPath>();
        enda1->D = "M0,0 L0,12 L12,6 z";
        enda1->Fill = "black";
        end_arrow_tri->add(enda1);
        arrows["end_arrow_tri"] = end_arrow_tri;
        Defs.push_back(end_arrow_tri);

        start_arrow_tri = std::make_shared<Lewzen::SVGIMarker>();
        start_arrow_tri->Id = "start_arrow_tri";
        start_arrow_tri->MarkerHeight = 13;
        start_arrow_tri->MarkerWidth = 13;
        start_arrow_tri->RefX = 0;
        start_arrow_tri->RefY = 6;
        start_arrow_tri->Orient = "auto";
        start_arrow_tri->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> enda2 = std::make_shared<Lewzen::SVGIPath>();
        enda2->D = "M12,0 L12,12 L0,6 z";
        enda2->Fill = "black";
        start_arrow_tri->add(enda2);
        arrows["start_arrow_tri"] = start_arrow_tri;
        Defs.push_back(start_arrow_tri);
//wwwwwwwwwwwwwwwwwwwwww
        end_arrow_line = std::make_shared<Lewzen::SVGIMarker>();
        end_arrow_line->Id = "end_arrow_line";
        end_arrow_line->MarkerHeight = 13;
        end_arrow_line->MarkerWidth = 13;
        end_arrow_line->RefX = 12;
        end_arrow_line->RefY = 6;
        end_arrow_line->Orient = "auto";
        end_arrow_line->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> enda3 = std::make_shared<Lewzen::SVGIPath>();
        enda3->D = "M0,0  L12,6 L 0,12 ";
        enda3->Fill = "none";
        enda3->Stroke = "black";
        end_arrow_line->add(enda3);
        arrows["end_arrow_line"] = end_arrow_line;
        Defs.push_back(end_arrow_line);

        start_arrow_line = std::make_shared<Lewzen::SVGIMarker>();
        start_arrow_line->Id = "start_arrow_line";
        start_arrow_line->MarkerHeight = 13;
        start_arrow_line->MarkerWidth = 13;
        start_arrow_line->RefX = 0;
        start_arrow_line->RefY = 6;
        start_arrow_line->Orient = "auto";
        start_arrow_line->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> end3 = std::make_shared<Lewzen::SVGIPath>();
        end3->D = "M12,0  L0,6 L 12,12 ";
        end3->Fill = "none";
        end3->Stroke = "black";
        start_arrow_line->add(end3);
        arrows["start_arrow_line"] = start_arrow_line;
        Defs.push_back(start_arrow_line);

        end_arrow_tri_h = std::make_shared<Lewzen::SVGIMarker>();
        end_arrow_tri_h->Id = "end_arrow_tri_h";
        end_arrow_tri_h->MarkerHeight = 13;
        end_arrow_tri_h->MarkerWidth = 13;
        end_arrow_tri_h->RefX = 12;
        end_arrow_tri_h->RefY = 6;
        end_arrow_tri_h->Orient = "auto";
        end_arrow_tri_h->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> end2 = std::make_shared<Lewzen::SVGIPath>();
        end2->D = "M0,0 L0,12 L12,6 z";
        end2->Fill = "white";
        end2->Stroke = "black";
        end_arrow_tri_h->add(end2);
        arrows["end_arrow_tri_h"] = end_arrow_tri_h;
        Defs.push_back(end_arrow_tri_h);

        start_arrow_tri_h = std::make_shared<Lewzen::SVGIMarker>();
        start_arrow_tri_h->Id = "start_arrow_tri_h";
        start_arrow_tri_h->MarkerHeight = 13;
        start_arrow_tri_h->MarkerWidth = 13;
        start_arrow_tri_h->RefX = 0;
        start_arrow_tri_h->RefY = 6;
        start_arrow_tri_h->Orient = "auto";
        start_arrow_tri_h->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> end1 = std::make_shared<Lewzen::SVGIPath>();
        end1->D = "M12,0 L12,12 L0,6 z";
        end1->Fill = "white";
        end1->Stroke = "black";
        start_arrow_tri_h->add(end1);
        arrows["start_arrow_tri_h"] = start_arrow_tri_h;
        Defs.push_back(start_arrow_tri_h);

        end_arrow_vline = std::make_shared<Lewzen::SVGIMarker>();
        end_arrow_vline->Id = "end_arrow_vline";
        end_arrow_vline->MarkerHeight = 13;
        end_arrow_vline->MarkerWidth = 13;
        end_arrow_vline->RefX = 0;
        end_arrow_vline->RefY = 6;
        end_arrow_vline->Orient = "auto";
        end_arrow_vline->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> end0 = std::make_shared<Lewzen::SVGIPath>();
        end0->D = "M0,0 L0,12 L2,12 L2,0 z";
        end0->Fill = "black";
        end0->Stroke = "black";
        end_arrow_vline->add(end0);
        arrows["end_arrow_vline"] = end_arrow_vline;
        Defs.push_back(end_arrow_vline);

        start_arrow_vline = std::make_shared<Lewzen::SVGIMarker>();
        start_arrow_vline->Id = "start_arrow_vline";
        start_arrow_vline->MarkerHeight = 13;
        start_arrow_vline->MarkerWidth = 13;
        start_arrow_vline->RefX = 2;
        start_arrow_vline->RefY = 6;
        start_arrow_vline->Orient = "auto";
        start_arrow_vline->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> e0 = std::make_shared<Lewzen::SVGIPath>();
        e0->D = "M2,0 L2,12 L0,12 L0,0 z";
        e0->Fill = "black";
        e0->Stroke = "black";
        start_arrow_vline->add(e0);
        arrows["start_arrow_vline"] = start_arrow_vline;
        Defs.push_back(start_arrow_vline);

        end_arrow_tri_half = std::make_shared<Lewzen::SVGIMarker>();
        end_arrow_tri_half->Id = "end_arrow_tri_half";
        end_arrow_tri_half->MarkerHeight = 13;
        end_arrow_tri_half->MarkerWidth = 13;
        end_arrow_tri_half->RefX = 12;
        end_arrow_tri_half->RefY = 6;
        end_arrow_tri_half->Orient = "auto";
        end_arrow_tri_half->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> e1 = std::make_shared<Lewzen::SVGIPath>();
        e1->D = "M0,0 L0,6 L12,6 z";
        e1->Fill = "black";
        e1->Stroke = "black";
        end_arrow_tri_half->add(e1);
        arrows["end_arrow_tri_half"] = end_arrow_tri_half;
        Defs.push_back(end_arrow_tri_half);


        start_arrow_tri_half = std::make_shared<Lewzen::SVGIMarker>();
        start_arrow_tri_half->Id = "start_arrow_tri_half";
        start_arrow_tri_half->MarkerHeight = 13;
        start_arrow_tri_half->MarkerWidth = 13;
        start_arrow_tri_half->RefX = 0;
        start_arrow_tri_half->RefY = 6;
        start_arrow_tri_half->Orient = "auto";
        start_arrow_tri_half->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> e2 = std::make_shared<Lewzen::SVGIPath>();
        e2->D = "M12,0 L12,6 L0,6 z";
        e2->Fill = "black";
        e2->Stroke = "black";
        start_arrow_tri_half->add(e2);
        arrows["start_arrow_tri_half"] = start_arrow_tri_half;
        Defs.push_back(start_arrow_tri_half);

        end_arrow_two_tri = std::make_shared<Lewzen::SVGIMarker>();
        end_arrow_two_tri->Id = "end_arrow_two_tri";
        end_arrow_two_tri->MarkerHeight = 23;
        end_arrow_two_tri->MarkerWidth = 23;
        end_arrow_two_tri->RefX = 20;
        end_arrow_two_tri->RefY = 6;
        end_arrow_two_tri->Orient = "auto";
        end_arrow_two_tri->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> e3 = std::make_shared<Lewzen::SVGIPath>();
        e3->D = "M0,2 L8,6 L0,10 z M8,0 L20,6 L8,12 z";
        e3->Fill = "black";
        e3->Stroke = "black";
        end_arrow_two_tri->add(e3);
        arrows["end_arrow_two_tri"] = end_arrow_two_tri;
        Defs.push_back(end_arrow_two_tri);

        start_arrow_two_tri = std::make_shared<Lewzen::SVGIMarker>();
        start_arrow_two_tri->Id = "start_arrow_two_tri";
        start_arrow_two_tri->MarkerHeight = 23;
        start_arrow_two_tri->MarkerWidth = 23;
        start_arrow_two_tri->RefX = 0;
        start_arrow_two_tri->RefY = 6;
        start_arrow_two_tri->Orient = "auto";
        start_arrow_two_tri->MarkerUnits = "userSpaceOnUse";
        std::shared_ptr<Lewzen::SVGIPath> e4 = std::make_shared<Lewzen::SVGIPath>();
        e4->D = "M20,2 L12,6 L20,10 z M12,0 L0,6 L12,12 z";
        e4->Fill = "black";
        e4->Stroke = "black";
        start_arrow_two_tri->add(e4);
        arrows["start_arrow_two_tri"] = start_arrow_two_tri;
        Defs.push_back(start_arrow_two_tri);

        hallow_line_arrow = std::make_shared<Lewzen::SVGIMarker>();
        hallow_line_arrow->Id = "hallow_line_arrow";
        hallow_line_arrow->MarkerHeight = 20;
        hallow_line_arrow->MarkerWidth = 20;
        hallow_line_arrow->RefX = 0;
        hallow_line_arrow->RefY = 6;
        hallow_line_arrow->Orient = "auto";
        std::shared_ptr<Lewzen::SVGIPath> h = std::make_shared<Lewzen::SVGIPath>();
        h->D = "M0,6 L0,0 L15,9 L0,18 L0,12";
        h->Fill = "none";
        h->Stroke = "black";
        hallow_line_arrow->add(h);
        arrows["hallow_line_arrow"] = hallow_line_arrow;
        Defs.push_back(hallow_line_arrow);


        for (auto p: Defs) {
            auto pp = p.lock();
            pp->commit();
        }
    }

    const std::string &Line::getLineType() const {
        return lineType;
    }

    void Line::set_line_type(std::string lt) {
        lineType = lt;
    }

    const std::string &Line::getDotType() const {
        return dotType;
    }

    double Line::getOffset() const {
        return offset;
    }

    void Line::setOffset(double offset) {
        Line::offset = offset;
    }
}

