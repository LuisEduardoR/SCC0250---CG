// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "TestScene.hpp"

# include <memory>
# include <vector>

# include "Geometry.hpp"
# include "ShapeRenderer.hpp"
# include "Transform.hpp"
# include "Moveable.hpp"
# include "Vector.hpp"
# include "Matrix4x4.hpp"
# include "CircleCollider.hpp"
# include "Player.hpp"
# include "PoissonDiscSampling.hpp"

using namespace Adven;

namespace
{

auto ShipModel() -> Shape2DCollection
{
    Shape2DCollection shipModel( new std::vector<std::unique_ptr<Shape2D>>{});
    // Ship Cannons
    shipModel.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.405f, +0.264f }, { -0.304f, +0.263f },
        { -0.405f, -0.196f }, { -0.304f, -0.196f },
        Color::blue
    }});
    shipModel.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { +0.304f, +0.264f }, { +0.405f, +0.263f },
        { +0.304f, -0.196f }, { +0.405f, -0.196f },
        Color::blue
    }});
    // Ship Thruster
    shipModel.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.190f, -0.455f }, { +0.213f, -0.455f },
        { -0.150f, -0.728f }, { +0.150f, -0.728f },
        Color::grey
    }});
    // Ship Base 
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, +0.660f }, { -0.231f, +0.048f }, { +0.231f, +0.048f }, Color::yellow
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.231f, +0.048f }, { +0.231f, +0.048f }, { -0.526f, -0.205f }, Color::yellow
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.231f, +0.048f }, { -0.526f, -0.205f }, { +0.526f, -0.205f }, Color::yellow
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.526f, -0.205f }, { -0.190f, -0.455f }, { +0.190f, -0.455f }, Color::yellow
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.526f, -0.205f }, { +0.526f, -0.205f }, { +0.190f, -0.455f }, Color::yellow
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.526f, -0.205f }, { -0.190f, -0.455f }, { -0.581f, -0.744f }, Color::yellow
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.526f, -0.205f }, { +0.190f, -0.455f }, { +0.581f, -0.744f }, Color::yellow
    }});
    // Ship Window
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, +0.530f }, { -0.194f, -0.074f }, { +0.194f, -0.074f }, Color::blue
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -0.290f }, { -0.194f, -0.074f }, { +0.194f, -0.074f }, Color::blue
    }});
    // Ship Circles
    shipModel.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -0.357f, -0.354f }, 0.125f, 8, Color::blue
    }});
    shipModel.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +0.357f, -0.354f }, 0.125f, 8, Color::blue
    }});

    return shipModel;
}

auto BossModel() -> Shape2DCollection
{
    Shape2DCollection boss( new std::vector<std::unique_ptr<Shape2D>>{});

    // Boss Base
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -207.000f }, { -80.000f, -76.950f }, { -50.000f, -18.320f }, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -207.000f }, { -50.000f, -18.320f }, { +0.000f, +0.000f }, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -207.000f }, { +0.000f, +0.000f }, { +50.000f, -18.320f }, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -207.000f }, { 50.000f, -18.320f }, { +80.000f, -77.000f }, Color(31, 40, 126)
    }});

    // Boss Window
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -167.000f }, { -54.000f, -75.890f }, { -33.750f, -34.830f }, Color(67, 39, 197)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -167.000f }, { -33.750f, -34.830f }, { +0.000f, -22.000f }, Color(67, 39, 197)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -167.000f }, { +0.000f, -22.000f }, { +33.750f, -34.830f }, Color(67, 39, 197)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -167.000f }, { +33.750f, -34.830f }, { +54.000f, -75.890f }, Color(67, 39, 197)
    }});

    // Boss body shape
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -207.000f }, { -90.000f, -170.250f }, { -80.00, -76.94f }, Color(117, 72, 138)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -207.000f }, { 90.000f, -170.250f }, { +80.000f, -77.000f }, Color(117, 72, 138)
    }});

    // Boss Big Claw Left
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -73.000f, -67.500f }, { -152.000f, 26.000f }, { -59.000f, -35.500f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -152.000f, 26.000f }, { -59.000f, -35.500f }, { -110.000f, +26.000f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -152.000f, 26.000f }, { -110.000f, +26.000f }, { -59.000f, +122.000f }, Color(195, 195, 195)
    }});

    // Boss Big Claw Right
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +73.000f, -67.500f }, { +152.000f, 26.000f }, { +59.000f, -35.500f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +152.000f, 26.000f }, { +59.000f, -35.500f }, { +110.000f, +26.000f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +152.000f, 26.000f }, { +110.000f, +26.000f }, { +59.000f, +122.000f }, Color(195, 195, 195)
    }});

    // Boss Small Claw Left
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -50.000f, -18.320f }, { -80.000f, +22.130f }, { -34.500f, -12.640f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -80.000f, +22.130f }, { -34.500f, -12.640f }, { -58.140f, +22.130f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -80.000f, +22.130f }, { -58.140f, +22.130f }, { -35.470f, +81.000f }, Color(195, 195, 195)
    }});

    // Boss Small Claw Right
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +50.000f, -18.320f }, { +80.000f, +22.130f }, { +34.500f, -12.640f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +80.000f, +22.130f }, { +34.500f, -12.640f }, { +58.140f, +22.130f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +80.000f, +22.130f }, { +58.140f, +22.130f }, { +35.470f, +81.000f }, Color(195, 195, 195)
    }});

    // Center Orb
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +3.000f, +92.000f }, 40.000f, 32
    }});

    // Left Cannon
    boss.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { -295.000f, +90.000f }, { -285.000f, +90.000f },
        { -295.000f, +120.000f }, { -285.000f, +120.000f },
        Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { -277.000f, +96.000f }, { -259.000f, +96.000f },
        { -277.000f, +153.000f }, { -259.000f, +153.000f },
        Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { -251.000f, +90.000f }, { -241.000f, +90.000f },
        { -251.000f, +120.000f }, { -241.000f, +120.000f },
        Color(195, 195, 195)
    }});
    
    // Right Cannon
    boss.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { +295.000f, +90.000f }, { +285.000f, +90.000f },
        { +295.000f, +120.000f }, { +285.000f, +120.000f },
        Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { +277.000f, +96.000f }, { +259.000f, +96.000f },
        { +277.000f, +153.000f }, { +259.000f, +153.000f },
        Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { +251.000f, +90.000f }, { +241.000f, +90.000f },
        { +251.000f, +120.000f }, { +241.000f, +120.000f },
        Color(195, 195, 195)
    }});

    // Tail Left
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -59.000f, -227.000f }, 40.000f, 32, Color(117, 72, 138)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -139.000f, -215.000f }, 40.000f, 32, Color(117, 72, 138)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -204.000f, -167.000f }, 40.000f, 32, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -239.000f, -95.000f }, 40.000f, 32, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -261.000f, -18.000f }, 40.000f, 32, Color(67, 39, 197)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -268.000f, +62.000f }, 40.000f, 32, Color(67, 39, 197)
    }});

     // Tail Right
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +59.000f, -227.000f }, 40.000f, 32, Color(117, 72, 138)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +139.000f, -215.000f }, 40.000f, 32, Color(117, 72, 138)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +204.000f, -167.000f }, 40.000f, 32, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +239.000f, -95.000f }, 40.000f, 32, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +261.000f, -18.000f }, 40.000f, 32, Color(67, 39, 197)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +268.000f, +62.000f }, 40.000f, 32, Color(67, 39, 197)
    }});

    return boss;
}

auto SkyModel() -> Shape2DCollection
{
    std::vector<Vector2> skyPoints{
        amn::PoissonDiscSampler::GeneratePoints(0.02f, { 2.0f, 2.0f }, 5)
    };

    Shape2DCollection skyModel{ new std::vector<std::unique_ptr<Shape2D>>{} };

    for (Vector2 point : skyPoints)
    {
        skyModel->push_back(std::unique_ptr<Point>{ new Point{
            point, Color::white
        }});
    }

    return skyModel;
}

}

TestScene::TestScene()
{
    // Vertex Shader's GLSL code
    std::string vertexCode =
    "attribute vec3 position;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = transform * vec4(position, 1.0);\n"
    "}\n";

    // Fragment Shader's GLSL code
    std::string fragmentCode =
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = color;\n"
    "}\n";

    // Creates the program we are going to use from our vertex and fragment shader's source code
    Renderer::SetProgram(vertexCode, fragmentCode);

    Shape2DCollection shipModel = ShipModel();
    Shape2DCollection bossModel = BossModel();
    Shape2DCollection skyModel = SkyModel();


    GameObject& ship = AddGameObject({});

    ship.AddComponent<Transform>(
        Vector3{ 0.0f, -0.3f, 0.0f },
        Vector3{},
        Vector3{ 0.3f, 0.3f, 1.0f });
    ship.AddComponent<ShapeRenderer>(shipModel);
    ship.AddComponent<Moveable>();
    ship.AddComponent<CircleCollider>(0.66f * 0.3f, true);
    ship.AddComponent<Player>();

    GameObject& boss = AddGameObject({});

    boss.AddComponent<Transform>(
        Vector3{ 0.0f, 0.4f, 0.0f },
        Vector3{ 0.0f, 0.0f, CONST_PI },
        Vector3{ 0.0025f, 0.0025f, 0.0f });
    boss.AddComponent<ShapeRenderer>(bossModel);
    boss.AddComponent<Moveable>();
    boss.AddComponent<CircleCollider>(0.66f * 0.3f, true);

    GameObject& sky = AddGameObject({});
    sky.AddComponent<Transform>(Vector3 { -1.0f, -1.0f, 0.0f });
    sky.AddComponent<ShapeRenderer>(skyModel);
}