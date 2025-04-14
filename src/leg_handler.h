#ifndef LEG_HANDLER_H
#define LEG_HANDLER_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/classes/marker3d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

class LegHandler : public Node3D {
    GDCLASS(LegHandler, Node3D);

private:

    bool handlerReady;

    float timeOffset;
    float step_distance;
    float checkerCooldown;
    float checkTime;
    float stepsTaken;
    float timeAccumulator;
    bool stepping;

    // Node3D* leg_1;
    // Node3D* leg_2;
    // Node3D* leg_3;
    // Node3D* leg_4;
    // Node3D* leg_5;
    // Node3D* leg_6;
    // Node3D* leg_7;
    // Node3D* leg_8;

    // Node3D* legtrgt_1;
    // Node3D* legtrgt_2;
    // Node3D* legtrgt_3;
    // Node3D* legtrgt_4;
    // Node3D* legtrgt_5;
    // Node3D* legtrgt_6;
    // Node3D* legtrgt_7;
    // Node3D* legtrgt_8;

    // std::array<Node3D*, 8> leg_array;
    // std::array<Node3D*, 8> legtrgt_array;

    // Leg and target paths
    NodePath leg_1;
    NodePath leg_2;
    NodePath leg_3;
    NodePath leg_4;
    NodePath leg_5;
    NodePath leg_6;
    NodePath leg_7;
    NodePath leg_8;

    NodePath legtrgt_1;
    NodePath legtrgt_2;
    NodePath legtrgt_3;
    NodePath legtrgt_4;
    NodePath legtrgt_5;
    NodePath legtrgt_6;
    NodePath legtrgt_7;
    NodePath legtrgt_8;

    std::array<NodePath, 8> leg_array;
    std::array<NodePath, 8> legtrgt_array;

protected:
    static void _bind_methods();

public:

    void _ready() override; //checkerCooldown = 0, stepping = false
    void _exit_tree() override;
    void validateLegs();
    void _process(double delta) override; // if stepping, stepLegs(). if checkerCooldown < checkTime, checkerCooldown += delta, else checkLegs();
    void checkLegs(); //for loop from 0-num legs, if distance between leg and its step target > step_distance, stepLegs();
    void stepLegs(double delta); //for loop from 0-num legs, step one leg, after time offset step step next
    void startCooldown(); //checkerCooldown = 0

    void set_timeOffset(float offset);
    float get_timeOffset() const;

    void set_checkTime(float time);
    float get_checkTime() const;

    void set_stepDistance(float distance);
    float get_stepDistance() const;

    // void set_leg_1(Node3D* leg);
    // Node3D* get_leg_1() const;

    // void set_leg_2(Node3D* leg);
    // Node3D* get_leg_2() const;

    // void set_leg_3(Node3D* leg);
    // Node3D* get_leg_3() const;

    // void set_leg_4(Node3D* leg);
    // Node3D* get_leg_4() const;

    // void set_leg_5(Node3D* leg);
    // Node3D* get_leg_5() const;

    // void set_leg_6(Node3D* leg);
    // Node3D* get_leg_6() const;

    // void set_leg_7(Node3D* leg);
    // Node3D* get_leg_7() const;

    // void set_leg_8(Node3D* leg);
    // Node3D* get_leg_8() const;

    // void set_legtrgt_1(Node3D* leg);
    // Node3D* get_legtrgt_1() const;

    // void set_legtrgt_2(Node3D* leg);
    // Node3D* get_legtrgt_2() const;

    // void set_legtrgt_3(Node3D* leg);
    // Node3D* get_legtrgt_3() const;

    // void set_legtrgt_4(Node3D* leg);
    // Node3D* get_legtrgt_4() const;

    // void set_legtrgt_5(Node3D* leg);
    // Node3D* get_legtrgt_5() const;

    // void set_legtrgt_6(Node3D* leg);
    // Node3D* get_legtrgt_6() const;

    // void set_legtrgt_7(Node3D* leg);
    // Node3D* get_legtrgt_7() const;

    // void set_legtrgt_8(Node3D* leg);
    // Node3D* get_legtrgt_8() const;

    bool is_Ready();
    void set_readyFlag(bool flag);

    void set_leg_1(NodePath leg);
    NodePath get_leg_1() const;

    void set_leg_2(NodePath leg);
    NodePath get_leg_2() const;

    void set_leg_3(NodePath leg);
    NodePath get_leg_3() const;

    void set_leg_4(NodePath leg);
    NodePath get_leg_4() const;

    void set_leg_5(NodePath leg);
    NodePath get_leg_5() const;

    void set_leg_6(NodePath leg);
    NodePath get_leg_6() const;

    void set_leg_7(NodePath leg);
    NodePath get_leg_7() const;

    void set_leg_8(NodePath leg);
    NodePath get_leg_8() const;

    void set_legtrgt_1(NodePath leg);
    NodePath get_legtrgt_1() const;

    void set_legtrgt_2(NodePath leg);
    NodePath get_legtrgt_2() const;

    void set_legtrgt_3(NodePath leg);
    NodePath get_legtrgt_3() const;

    void set_legtrgt_4(NodePath leg);
    NodePath get_legtrgt_4() const;

    void set_legtrgt_5(NodePath leg);
    NodePath get_legtrgt_5() const;

    void set_legtrgt_6(NodePath leg);
    NodePath get_legtrgt_6() const;

    void set_legtrgt_7(NodePath leg);
    NodePath get_legtrgt_7() const;

    void set_legtrgt_8(NodePath leg);
    NodePath get_legtrgt_8() const;

};

}

#endif // LEG_HANDLER_H