#include "leg_handler.h"

using namespace godot;

void LegHandler::_bind_methods() {

    ClassDB::bind_method(D_METHOD("checkLegs"), &LegHandler::checkLegs);
    ClassDB::bind_method(D_METHOD("stepLegs"), &LegHandler::stepLegs);
    ClassDB::bind_method(D_METHOD("startCooldown"), &LegHandler::startCooldown);

    ClassDB::bind_method(D_METHOD("validateLegs"), &LegHandler::validateLegs);
    ClassDB::bind_method(D_METHOD("is_Ready"), &LegHandler::is_Ready);
    ClassDB::bind_method(D_METHOD("set_readyFlag", "flag"), &LegHandler::set_readyFlag);

    // Export timeOffset
    ClassDB::bind_method(D_METHOD("set_timeOffset", "offset"), &LegHandler::set_timeOffset);
    ClassDB::bind_method(D_METHOD("get_timeOffset"), &LegHandler::get_timeOffset);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "time_offset"), "set_timeOffset", "get_timeOffset");

    // Export step_distance
    ClassDB::bind_method(D_METHOD("set_stepDistance", "distance"), &LegHandler::set_stepDistance);
    ClassDB::bind_method(D_METHOD("get_stepDistance"), &LegHandler::get_stepDistance);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "step_distance"), "set_stepDistance", "get_stepDistance");

    // Export step_distance
    ClassDB::bind_method(D_METHOD("set_checkTime", "time"), &LegHandler::set_checkTime);
    ClassDB::bind_method(D_METHOD("get_checkTime"), &LegHandler::get_checkTime);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "checkTime"), "set_checkTime", "get_checkTime");

    // Export leg_1 through leg_8
    ClassDB::bind_method(D_METHOD("set_leg_1", "leg"), &LegHandler::set_leg_1);
    ClassDB::bind_method(D_METHOD("get_leg_1"), &LegHandler::get_leg_1);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "leg_1"), "set_leg_1", "get_leg_1");

    ClassDB::bind_method(D_METHOD("set_leg_2", "leg"), &LegHandler::set_leg_2);
    ClassDB::bind_method(D_METHOD("get_leg_2"), &LegHandler::get_leg_2);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "leg_2"), "set_leg_2", "get_leg_2");

    ClassDB::bind_method(D_METHOD("set_leg_3", "leg"), &LegHandler::set_leg_3);
    ClassDB::bind_method(D_METHOD("get_leg_3"), &LegHandler::get_leg_3);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "leg_3"), "set_leg_3", "get_leg_3");

    ClassDB::bind_method(D_METHOD("set_leg_4", "leg"), &LegHandler::set_leg_4);
    ClassDB::bind_method(D_METHOD("get_leg_4"), &LegHandler::get_leg_4);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "leg_4"), "set_leg_4", "get_leg_4");

    ClassDB::bind_method(D_METHOD("set_leg_5", "leg"), &LegHandler::set_leg_5);
    ClassDB::bind_method(D_METHOD("get_leg_5"), &LegHandler::get_leg_5);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "leg_5"), "set_leg_5", "get_leg_5");

    ClassDB::bind_method(D_METHOD("set_leg_6", "leg"), &LegHandler::set_leg_6);
    ClassDB::bind_method(D_METHOD("get_leg_6"), &LegHandler::get_leg_6);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "leg_6"), "set_leg_6", "get_leg_6");

    ClassDB::bind_method(D_METHOD("set_leg_7", "leg"), &LegHandler::set_leg_7);
    ClassDB::bind_method(D_METHOD("get_leg_7"), &LegHandler::get_leg_7);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "leg_7"), "set_leg_7", "get_leg_7");

    ClassDB::bind_method(D_METHOD("set_leg_8", "leg"), &LegHandler::set_leg_8);
    ClassDB::bind_method(D_METHOD("get_leg_8"), &LegHandler::get_leg_8);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "leg_8"), "set_leg_8", "get_leg_8");

    // Leg Target bindings
    ClassDB::bind_method(D_METHOD("set_legtrgt_1", "legtrgt"), &LegHandler::set_legtrgt_1);
    ClassDB::bind_method(D_METHOD("get_legtrgt_1"), &LegHandler::get_legtrgt_1);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "legtrgt_1"), "set_legtrgt_1", "get_legtrgt_1");

    ClassDB::bind_method(D_METHOD("set_legtrgt_2", "legtrgt"), &LegHandler::set_legtrgt_2);
    ClassDB::bind_method(D_METHOD("get_legtrgt_2"), &LegHandler::get_legtrgt_2);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "legtrgt_2"), "set_legtrgt_2", "get_legtrgt_2");

    ClassDB::bind_method(D_METHOD("set_legtrgt_3", "legtrgt"), &LegHandler::set_legtrgt_3);
    ClassDB::bind_method(D_METHOD("get_legtrgt_3"), &LegHandler::get_legtrgt_3);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "legtrgt_3"), "set_legtrgt_3", "get_legtrgt_3");

    ClassDB::bind_method(D_METHOD("set_legtrgt_4", "legtrgt"), &LegHandler::set_legtrgt_4);
    ClassDB::bind_method(D_METHOD("get_legtrgt_4"), &LegHandler::get_legtrgt_4);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "legtrgt_4"), "set_legtrgt_4", "get_legtrgt_4");

    ClassDB::bind_method(D_METHOD("set_legtrgt_5", "legtrgt"), &LegHandler::set_legtrgt_5);
    ClassDB::bind_method(D_METHOD("get_legtrgt_5"), &LegHandler::get_legtrgt_5);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "legtrgt_5"), "set_legtrgt_5", "get_legtrgt_5");

    ClassDB::bind_method(D_METHOD("set_legtrgt_6", "legtrgt"), &LegHandler::set_legtrgt_6);
    ClassDB::bind_method(D_METHOD("get_legtrgt_6"), &LegHandler::get_legtrgt_6);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "legtrgt_6"), "set_legtrgt_6", "get_legtrgt_6");

    ClassDB::bind_method(D_METHOD("set_legtrgt_7", "legtrgt"), &LegHandler::set_legtrgt_7);
    ClassDB::bind_method(D_METHOD("get_legtrgt_7"), &LegHandler::get_legtrgt_7);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "legtrgt_7"), "set_legtrgt_7", "get_legtrgt_7");

    ClassDB::bind_method(D_METHOD("set_legtrgt_8", "legtrgt"), &LegHandler::set_legtrgt_8);
    ClassDB::bind_method(D_METHOD("get_legtrgt_8"), &LegHandler::get_legtrgt_8);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "legtrgt_8"), "set_legtrgt_8", "get_legtrgt_8");

}

void LegHandler::_ready() {
    stepsTaken = 0.0;
    stepping = false;
    startCooldown();
    leg_array = {leg_1, leg_2, leg_3, leg_4, leg_5, leg_6, leg_7, leg_8};
    legtrgt_array = {legtrgt_1, legtrgt_2, legtrgt_3, legtrgt_4, legtrgt_5, legtrgt_6, legtrgt_7, legtrgt_8};
    validateLegs();
    print_line(handlerReady);
}

void LegHandler::_exit_tree() {
    validateLegs();
    if (is_Ready()) {
        set_readyFlag(false);
    }
}

void LegHandler::validateLegs() {
    for (int i = 0; i < 8; i++) {
        if (leg_array[i].is_empty() || legtrgt_array[i].is_empty()) {
            set_readyFlag(false);
            return;
        }
    }

    set_readyFlag(true);

}

void LegHandler::_process(double delta) {
    if (!is_Ready()) {
        validateLegs();
        return;
    }

    if (stepping) {
        stepLegs(delta);
    } else if (checkerCooldown < checkTime) {
        checkerCooldown += delta;
    } else {
        checkLegs();
    }

}

void LegHandler::checkLegs() { //for loop from 0-num legs, if distance between leg and its step target > step_distance, stepLegs();
    
    for (int i = 0; i < 8; i++) {
        Node3D* leg = get_node<Node3D>(leg_array[i]);
        Node3D* target = get_node<Node3D>(legtrgt_array[i]);
    
        if (!leg || !target) continue;
    
        float dist = leg->get_global_position().distance_to(target->get_global_position());
    
        if (dist > step_distance) {
            stepping = true;
        }
    }
}

void LegHandler::stepLegs(double delta) {
    timeAccumulator += delta;

    if (timeAccumulator >= timeOffset) {
        Node* node = get_node<Node>(leg_array[stepsTaken]);
        if (node && node->has_method("step")) {
            node->call("step");
        }
        timeAccumulator = 0.0;
        stepsTaken++;
    }

    if (stepsTaken > 7) {
        stepsTaken = 0;
        stepping = false;
        startCooldown();
    }

}

void LegHandler::startCooldown() {
    checkerCooldown = 0;
}

//Get + Set Methods
void LegHandler::set_timeOffset(float offset) {
    timeOffset = offset;
}

float LegHandler::get_timeOffset() const{
    return timeOffset;
}

void LegHandler::set_stepDistance(float distance) {
    step_distance = distance;
}

float LegHandler::get_stepDistance() const{
    return step_distance;
}

void LegHandler::set_checkTime(float time) {
    checkTime = time;
}

float LegHandler::get_checkTime() const{
    return checkTime;
}

bool LegHandler::is_Ready() {
    return handlerReady;
}

void LegHandler::set_readyFlag(bool flag) {
    handlerReady = flag;
}

// //Get + Set Methods for each leg
// void LegHandler::set_leg_1(Node3D* leg) {
//     leg_1 = leg;
// }

// Node3D* LegHandler::get_leg_1() const{
//     return leg_1;
// }

// void LegHandler::set_leg_2(Node3D* leg) {
//     leg_2 = leg;
// }

// Node3D* LegHandler::get_leg_2() const{
//     return leg_2;
// }

// void LegHandler::set_leg_3(Node3D* leg) {
//     leg_3 = leg;
// }

// Node3D* LegHandler::get_leg_3() const{
//     return leg_3;
// }

// void LegHandler::set_leg_4(Node3D* leg) {
//     leg_4 = leg;
// }

// Node3D* LegHandler::get_leg_4() const{
//     return leg_4;
// }

// void LegHandler::set_leg_5(Node3D* leg) {
//     leg_5 = leg;
// }

// Node3D* LegHandler::get_leg_5() const{
//     return leg_5;
// }

// void LegHandler::set_leg_6(Node3D* leg) {
//     leg_6 = leg;
// }

// Node3D* LegHandler::get_leg_6() const{
//     return leg_6;
// }

// void LegHandler::set_leg_7(Node3D* leg) {
//     leg_7 = leg;
// }

// Node3D* LegHandler::get_leg_7() const{
//     return leg_7;
// }

// void LegHandler::set_leg_8(Node3D* leg) {
//     leg_8 = leg;
// }

// Node3D* LegHandler::get_leg_8() const{
//     return leg_8;
// }

// //Get + Set Methods for Leg Target
// void LegHandler::set_legtrgt_1(Node3D* legtrgt) {
//     legtrgt_1 = legtrgt;
// }

// Node3D* LegHandler::get_legtrgt_1() const{
//     return legtrgt_1;
// }

// void LegHandler::set_legtrgt_2(Node3D* legtrgt) {
//     legtrgt_2 = legtrgt;
// }

// Node3D* LegHandler::get_legtrgt_2() const{
//     return legtrgt_2;
// }

// void LegHandler::set_legtrgt_3(Node3D* legtrgt) {
//     legtrgt_3 = legtrgt;
// }

// Node3D* LegHandler::get_legtrgt_3() const{
//     return legtrgt_3;
// }

// void LegHandler::set_legtrgt_4(Node3D* legtrgt) {
//     legtrgt_4 = legtrgt;
// }

// Node3D* LegHandler::get_legtrgt_4() const{
//     return legtrgt_4;
// }

// void LegHandler::set_legtrgt_5(Node3D* legtrgt) {
//     legtrgt_5 = legtrgt;
// }

// Node3D* LegHandler::get_legtrgt_5() const{
//     return legtrgt_5;
// }

// void LegHandler::set_legtrgt_6(Node3D* legtrgt) {
//     legtrgt_6 = legtrgt;
// }

// Node3D* LegHandler::get_legtrgt_6() const{
//     return legtrgt_6;
// }

// void LegHandler::set_legtrgt_7(Node3D* legtrgt) {
//     legtrgt_7 = legtrgt;
// }

// Node3D* LegHandler::get_legtrgt_7() const{
//     return legtrgt_7;
// }

// void LegHandler::set_legtrgt_8(Node3D* legtrgt) {
//     legtrgt_8 = legtrgt;
// }

// Node3D* LegHandler::get_legtrgt_8() const{
//     return legtrgt_8;
// }

//Get + Set Methods for each leg
void LegHandler::set_leg_1(NodePath leg) {
    leg_1 = leg;
}

NodePath LegHandler::get_leg_1() const{
    return leg_1;
}

void LegHandler::set_leg_2(NodePath leg) {
    leg_2 = leg;
}

NodePath LegHandler::get_leg_2() const{
    return leg_2;
}

void LegHandler::set_leg_3(NodePath leg) {
    leg_3 = leg;
}

NodePath LegHandler::get_leg_3() const{
    return leg_3;
}

void LegHandler::set_leg_4(NodePath leg) {
    leg_4 = leg;
}

NodePath LegHandler::get_leg_4() const{
    return leg_4;
}

void LegHandler::set_leg_5(NodePath leg) {
    leg_5 = leg;
}

NodePath LegHandler::get_leg_5() const{
    return leg_5;
}

void LegHandler::set_leg_6(NodePath leg) {
    leg_6 = leg;
}

NodePath LegHandler::get_leg_6() const{
    return leg_6;
}

void LegHandler::set_leg_7(NodePath leg) {
    leg_7 = leg;
}

NodePath LegHandler::get_leg_7() const{
    return leg_7;
}

void LegHandler::set_leg_8(NodePath leg) {
    leg_8 = leg;
}

NodePath LegHandler::get_leg_8() const{
    return leg_8;
}

//Get + Set Methods for Leg Target
void LegHandler::set_legtrgt_1(NodePath legtrgt) {
    legtrgt_1 = legtrgt;
}

NodePath LegHandler::get_legtrgt_1() const{
    return legtrgt_1;
}

void LegHandler::set_legtrgt_2(NodePath legtrgt) {
    legtrgt_2 = legtrgt;
}

NodePath LegHandler::get_legtrgt_2() const{
    return legtrgt_2;
}

void LegHandler::set_legtrgt_3(NodePath legtrgt) {
    legtrgt_3 = legtrgt;
}

NodePath LegHandler::get_legtrgt_3() const{
    return legtrgt_3;
}

void LegHandler::set_legtrgt_4(NodePath legtrgt) {
    legtrgt_4 = legtrgt;
}

NodePath LegHandler::get_legtrgt_4() const{
    return legtrgt_4;
}

void LegHandler::set_legtrgt_5(NodePath legtrgt) {
    legtrgt_5 = legtrgt;
}

NodePath LegHandler::get_legtrgt_5() const{
    return legtrgt_5;
}

void LegHandler::set_legtrgt_6(NodePath legtrgt) {
    legtrgt_6 = legtrgt;
}

NodePath LegHandler::get_legtrgt_6() const{
    return legtrgt_6;
}

void LegHandler::set_legtrgt_7(NodePath legtrgt) {
    legtrgt_7 = legtrgt;
}

NodePath LegHandler::get_legtrgt_7() const{
    return legtrgt_7;
}

void LegHandler::set_legtrgt_8(NodePath legtrgt) {
    legtrgt_8 = legtrgt;
}

NodePath LegHandler::get_legtrgt_8() const{
    return legtrgt_8;
}