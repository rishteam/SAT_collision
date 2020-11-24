#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include "fmt/core.h"
#include "vector_math.h"

#include "Box.h"
#include "Circle.h"
#include "Polygon.h"
#include "Arbiter.h"

#include "imgui.h"
#include "imgui-SFML.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define UNIT 1
#define OBJ_COUNT 10

sf::Font font;
double timer = 0;
int cnt = 220;
int cnt2 = 0;
static bool f_keepSimulate = true;
static bool f_showContactPoints = true;
static int mode = 0;



World world(Vec2(0.0, -9.8), 1280.0f, 780.0f);
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,  WINDOW_HEIGHT), "Physics");

// Polygon-Polygon contact Point
//void PolygonToPolygonContactPoint(sf::Event event)
//{
//    std::deque<Vec2> tmp;
//    tmp.push_back({-10, 10});
//    tmp.push_back({10, 10});
//    tmp.push_back({10, -10});
//    tmp.push_back({0, -20});
//    tmp.push_back({-10, -10});
//
//    Shape *poly = new Polygon(tmp, Vec2(0, 0), 10.0f);
//    poly->SetMatrix(0.0f);
//
//    std::deque<Vec2> tmp2;
//    tmp2.push_back({-10, 10});
//    tmp2.push_back({10, 10});
//    tmp2.push_back({10, -10});
//    tmp2.push_back({0, -20});
//    tmp2.push_back({-10, -10});
//
//    Shape *poly2 = new Polygon(tmp, Vec2(0, 0), 10.0f);
//
//    poly2->setPosition(Vec2(event.mouseMove.x, event.mouseMove.y));
//
//    Arbiter tmpM(poly, poly2);
//
//    // Collide Detection
//    if (poly->Collide(tmpM, *poly2))
//    {
//        poly->selected = true;
//        poly2->selected = true;
//    }
//
//    // Draw
//    poly->setDebugDraw();
//    window.draw(*poly);
//    poly2->setDebugDraw();
//    window.draw(*poly2);
//
//    for(int i = 0; i < tmpM.contactCounter; i++)
//    {
//        sf::CircleShape circle;
//        circle.setRadius(5);
//        circle.setFillColor(sf::Color::Green);
//        Vec2 cp = World::ConvertWorldToScreen(Vec2(tmpM.contacts[i].position.x, tmpM.contacts[i].position.y));
//        circle.setOrigin(5, 5);
//        circle.setPosition(cp.x, cp.y);
//        window.draw(circle);
//    }
//}
//
//// Circle-Polygon contact Point
//void CircleToPolygonContactPoint(sf::Event event)
//{
//    std::deque<Vec2> tmp2;
//    tmp2.push_back({-10, 10});
//    tmp2.push_back({10, 10});
//    tmp2.push_back({10, -10});
//    tmp2.push_back({-10, -10});
//
//    Shape *poly = new Polygon(tmp2, Vec2(0, 0), 10.0f);
//    poly->SetMatrix(0.6666f);
//
//    Circle *circle = new Circle(10, 10, 10, 10);
//    Arbiter tmpM(poly, circle);
//
//    // Update with mouse
//    circle->setPosition(Vec2(event.mouseMove.x, event.mouseMove.y));
//
//    // Collide Detection
//    if (poly->Collide(tmpM, *circle))
//    {
//        poly->selected = true;
//        circle->selected = true;
//    }
//
//    // Draw
//    poly->setDebugDraw();
//    window.draw(*poly);
//    circle->setDebugDraw();
//    window.draw(*circle);
//
//    for(int i = 0; i < tmpM.contactCounter; i++)
//    {
//        sf::CircleShape circle;
//        circle.setRadius(5);
//        circle.setFillColor(sf::Color::Green);
//        Vec2 cp = World::ConvertWorldToScreen(Vec2(tmpM.contacts[i].position.x, tmpM.contacts[i].position.y));
//        circle.setOrigin(5, 5);
//        circle.setPosition(cp.x, cp.y);
//        window.draw(circle);
//    }
//}
//
//// Circle-Circle contact Point
//void CircleToCircleContactPoints(sf::Event event)
//{
//    Circle *circle = new Circle(10, 10, 10, 10);
//    Circle *circle2 = new Circle(10, 10, 5, 10);
//    Arbiter tmpM(circle, circle2);
//
//    // Update with mouse
//    circle2->setPosition(Vec2(event.mouseMove.x, event.mouseMove.y));
//
//    // Collide Detection
//    if (circle2->Collide(tmpM, *circle))
//    {
//        circle->selected = true;
//        circle2->selected = true;
//    }
//
//    // Draw
//    circle->setDebugDraw();
//    window.draw(*circle);
//    circle2->setDebugDraw();
//    window.draw(*circle2);
//
//    for(int i = 0; i < tmpM.contactCounter; i++)
//    {
//        sf::CircleShape circle;
//        circle.setRadius(5);
//        circle.setFillColor(sf::Color::Green);
//        Vec2 cp = World::ConvertWorldToScreen(Vec2(tmpM.contacts[i].position.x, tmpM.contacts[i].position.y));
//        circle.setOrigin(5, 5);
//        circle.setPosition(cp.x, cp.y);
//        window.draw(circle);
//    }
//};
//
//void BoxToBox(sf::Event event)
//{
//    Shape *box = new Box(0, 0, 10, 10, 10);
//    box->SetMatrix(0.6666f);
//
//    Shape *box2 = new Box(0, 0, 10, 10, 10);
//
//    // Update with mouse
//    box2->setPosition(Vec2(event.mouseMove.x, event.mouseMove.y));
//
//    Arbiter tmpM(box, box2);
//
//    // Collide Detection
//    if (box->Collide(tmpM, *box2))
//    {
//        box->selected = true;
//        box2->selected = true;
//    }
//
//    // Draw
//    box->setDebugDraw();
//    window.draw(*box);
//    box2->setDebugDraw();
//    window.draw(*box2);
//
//    for(int i = 0; i < tmpM.contactCounter; i++)
//    {
//        sf::CircleShape circle;
//        circle.setRadius(5);
//        circle.setFillColor(sf::Color::Green);
//        Vec2 cp = World::ConvertWorldToScreen(Vec2(tmpM.contacts[i].position.x, tmpM.contacts[i].position.y));
//        circle.setOrigin(5, 5);
//        circle.setPosition(cp.x, cp.y);
//        window.draw(circle);
//    }
//}

void generatePolygon(float x, float y)
{
    std::deque<Vec2> tmp;
    tmp.push_back({-5, 5});
    tmp.push_back({5, 5});
    tmp.push_back({5, -5});
    tmp.push_back({0, -10});
    tmp.push_back({-5, -5});

    Polygon *poly = new Polygon(tmp, Vec2(x, y), 10);
    world.Add(poly);
}


void generateBox(float x, float y)
{
    Box *box = new Box(x, y, 5, 5, 10);
    world.Add(box);
}

void generateCircle(float x, float y)
{
    Circle *circle = new Circle(x, y, 5, 10);
    world.Add(circle);
}

void PhysicsDemo1()
{
    std::deque<Vec2> tmp;
    tmp.push_back({-5, 5});
    tmp.push_back({5, 5});
    tmp.push_back({5, -5});
    tmp.push_back({0, -10});
    tmp.push_back({-5, -5});

//    Shape *poly = new Box(0, -5, 20, 5, FLT_MAX);


    Box *box = new Box(-10, 20, 5, 5, 10);
//    poly->SetMatrix(0.3333f);

    Box *floor = new Box(0, -20, 100, 5, FLT_MAX);
//    floor->SetMatrix(0.3333f);

    Box *floor2 = new Box(-35, -15, 20, 5, FLT_MAX);
//    floor2->SetMatrix(-0.3333f);
//
//    std::deque<Vec2> tmp2;
//    tmp2.push_back({-30, 10});
//    tmp2.push_back({30, 10});
//    tmp2.push_back({30, -10});
//    tmp2.push_back({-30, -10});
//
    Circle *circle = new Circle(-15, 20, 5, 10);
    Circle *circle2 = new Circle(-15, 0, 5, FLT_MAX);
//    world.Add(box);
//    world.Add(poly);
    world.Add(floor);
//    world.Add(floor2);
//    world.Add(circle2);
//    world.Add(circle);
//    world.Add(poly);
}

void drawObject()
{
    for(auto &bd : world.bodies)
    {
        bd->setDebugDraw();
        window.draw(*bd);
    }
}

void drawContact()
{
    for(auto &arb : world.arbiters)
    {
        for(int i = 0; i < arb.second.contactCounter; i++)
        {
            sf::CircleShape circle;
            circle.setRadius(5);
            circle.setFillColor(sf::Color::Green);
            Vec2 cp = World::ConvertWorldToScreen(Vec2(arb.second.contacts[i].position.x, arb.second.contacts[i].position.y));
            circle.setOrigin(5, 5);
            circle.setPosition(cp.x, cp.y);
            window.draw(circle);
        }
    }
}

int main()
{
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    std::cout << "wheel type: vertical" << std::endl;
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                    std::cout << "wheel type: horizontal" << std::endl;
                else
                    std::cout << "wheel type: unknown" << std::endl;
                std::cout << "wheel ent: " << event.mouseWheelScroll.delta << std::endl;
                std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                mode = 1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                mode = 2;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                mode = 3;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                Vec2 tmp = World::ChangeToPhysicsWorld(Vec2(event.mouseButton.x, event.mouseButton.y));
                switch(mode)
                {
                    case 1:
                    {
                        generateBox(tmp.x, tmp.y);
                        break;
                    }
                    case 2:
                    {
                        generatePolygon(tmp.x, tmp.y);
                        break;
                    }
                    case 3:
                    {
                        generateCircle(tmp.x, tmp.y);
                        break;
                    }
                }
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Contact Points Detection");
        if (ImGui::CollapsingHeader("Cases"))
        {
            if(ImGui::Button("Simple Demo"))
            {
                PhysicsDemo1();
            }
            if(ImGui::Button("Clear"))
            {
                world.Clear();
            }
        }

        for(int i = 0; i < world.bodies.size(); i++)
        {
            ImGui::Text("Object %d:", i);
            ImGui::Text("[Physics] Type: %d", world.bodies[i]->type);
            ImGui::Text("[Physics] Center: (%f, %f)", world.bodies[i]->position.x, world.bodies[i]->position.y);
            ImGui::Text("[Physics] angle: %f", radiansToDegrees(world.bodies[i]->angle) );
            ImGui::Text("[Physics] mass: %f", world.bodies[i]->mass);
            ImGui::Text("[Physics] Velocity: (%f, %f)", world.bodies[i]->velocity.x, world.bodies[i]->velocity.y);
            ImGui::Text("[Physics] Angular Velocity: %f", world.bodies[i]->angularVelocity);
            ImGui::Text("[Physics] invMass: %f", world.bodies[i]->invMass);
            ImGui::Text("[Physics] I: %f", world.bodies[i]->I);
            ImGui::Text("[Physics] invI: %f", world.bodies[i]->invI);
            ImGui::Text("[Physics] Friction: %f", world.bodies[i]->friction);
            ImGui::Separator();
        }

        ImGui::Text("Arbiters size: %d", world.arbList.size());
        for(auto arbiter : world.arbiters)
        {
//            ImGui::Text("Arbiters: Contact %d", arbiter.second.contactCounter);
//            ImGui::Text("Arbiters Contacts[0]: (%f, %f)", arbiter.second.contacts[0].position.x, arbiter.second.contacts[0].position.x);
//            ImGui::Text("Arbiters Contacts[0] Pn: %f", arbiter.second.contacts[0].Pn);
//            ImGui::Text("Arbiters Contacts[0] Pnb: %f", arbiter.second.contacts[0].Pnb);
//            ImGui::Text("Arbiters Contacts[0] Pt: %f", arbiter.second.contacts[0].Pt);
//            ImGui::Text("Arbiters Contacts[0] bias: %f", arbiter.second.contacts[0].bias);
//            ImGui::Text("Arbiters Contacts[0] penetration: %f", arbiter.second.contacts[0].penetration);
//
//            ImGui::Text("Arbiters Contacts[1]: (%f, %f)", arbiter.second.contacts[1].position.x, arbiter.second.contacts[1].position.x);
//            ImGui::Text("Arbiters b1: %d", arbiter.second.b1->type);
//            ImGui::Text("Arbiters b2: %d", arbiter.second.b2->type);
            ImGui::Separator();
        }

        ImGui::Text("[Window] width: %d", WINDOW_WIDTH);
        ImGui::Text("[Window] height: %d", WINDOW_HEIGHT);
        ImGui::Text("[Window] fps: %f", world.timeStep);
        ImGui::End();

        window.clear(sf::Color::Black);
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//        {
//            world.Step(world.timeStep);
//        }
        world.Step(world.timeStep);
        drawObject();
        drawContact();
        ImGui::SFML::Render(window);
        window.display();
    }
}