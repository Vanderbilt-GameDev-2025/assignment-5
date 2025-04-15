// #include "bodyRotation_handler.h"

// using namespace godot;

// void RotationHandler::_bind_methods() {

//     ClassDB::bind_method(D_METHOD("validateRays"), &RotationHandler::validateRays);
//     ClassDB::bind_method(D_METHOD("checkRotation"), &RotationHandler::checkRotation);
//     ClassDB::bind_method(D_METHOD("rotateXaxis", "delta"), &RotationHandler::rotateXaxis);
//     ClassDB::bind_method(D_METHOD("rotateZaxis", "delta"), &RotationHandler::rotateZaxis);
//     ClassDB::bind_method(D_METHOD("startCooldown"), &RotationHandler::startCooldown);

//     ClassDB::bind_method(D_METHOD("is_Ready"), &RotationHandler::is_Ready);
//     ClassDB::bind_method(D_METHOD("set_readyFlag", "flag"), &RotationHandler::set_readyFlag);

//     ClassDB::bind_method(D_METHOD("set_checkTime", "time"), &RotationHandler::set_checkTime);
//     ClassDB::bind_method(D_METHOD("get_checkTime"), &RotationHandler::get_checkTime);
//     ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "checkTime"), "set_checkTime", "get_checkTime");

//     ClassDB::bind_method(D_METHOD("set_rotationRay_Front", "ray"), &RotationHandler::set_rotationRay_Front);
//     ClassDB::bind_method(D_METHOD("get_rotationRay_Front"), &RotationHandler::get_rotationRay_Front);
//     ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "Front ray"), "set_rotationRay_Front", "get_rotationRay_Front");

//     ClassDB::bind_method(D_METHOD("set_rotationRay_Back", "ray"), &RotationHandler::set_rotationRay_Back);
//     ClassDB::bind_method(D_METHOD("get_rotationRay_Back"), &RotationHandler::get_rotationRay_Back);
//     ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "Back ray"), "set_rotationRay_Back", "get_rotationRay_Back");

//     ClassDB::bind_method(D_METHOD("set_rotationRay_Right", "ray"), &RotationHandler::set_rotationRay_Right);
//     ClassDB::bind_method(D_METHOD("get_rotationRay_Right"), &RotationHandler::get_rotationRay_Right);
//     ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "Right ray"), "set_rotationRay_Right", "get_rotationRay_Right");

//     ClassDB::bind_method(D_METHOD("set_rotationRay_Left", "ray"), &RotationHandler::set_rotationRay_Left);
//     ClassDB::bind_method(D_METHOD("get_rotationRay_Left"), &RotationHandler::get_rotationRay_Left);
//     ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "Left ray"), "set_rotationRay_Left", "get_rotationRay_Left");

//     ClassDB::bind_method(D_METHOD("set_rotationBody", "rotbody"), &RotationHandler::set_rotationBody);
//     ClassDB::bind_method(D_METHOD("get_rotationBody"), &RotationHandler::get_rotationBody);
//     ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "Rotation Body"), "set_rotationBody", "get_rotationBody");

// }

// void RotationHandler::_ready() {
//     handlerReady = rotatingXaxis = rotatingZaxis = false;
//     startCooldown();
//     rotationRay_array = {rotationRay_Front, rotationRay_Back, rotationRay_Right, rotationRay_Left};
//     //Left Right = Z axis, Front Back = X axis
//     validateRays();
// }

// void RotationHandler::_process(double delta) {
//     if (!is_Ready()) {
//         validateRays();
//         return;
//     }

//     if (rotatingXaxis) {
//         rotateXaxis(delta);
//     } else if (rotatingZaxis) {
//         rotateZaxis(delta);
//     } else if (checkerCooldown < checkTime) {
//         checkerCooldown += delta;
//     } else {
//         checkRotation();
//     }

// }

// void RotationHandler::validateRays() {
//     for (int i = 0; i < 4; i++) {
//         if (rotationRay_array[i].is_empty()) {
//             set_readyFlag(false);
//             return;
//         }
//     }

//     if (!rotationBody) {
//         set_readyFlag(false);
//         return;
//     }

//     set_readyFlag(true);
// }

// void RotationHandler::checkRotation() {



// }

// void RotationHandler::rotateXaxis(double delta) {

// }

// void RotationHandler::rotateZaxis(double delta) {

// }

// void RotationHandler::startCooldown() {
//     checkerCooldown = 0;
// }

// bool RotationHandler::is_Ready() {
//     return handlerReady;
// }

// void RotationHandler::set_readyFlag(bool flag) {
//     handlerReady = flag;
// }

// void RotationHandler::set_checkTime(float time) {
//     checkTime = time;
// }

// float RotationHandler::get_checkTime() const {
//     return checkTime;
// }

// void RotationHandler::set_rotationRay_Front(NodePath ray) {

// }

// NodePath RotationHandler::get_rotationRay_Front() const {

// }

// void RotationHandler::set_rotationRay_Back(NodePath ray) {

// }

// NodePath RotationHandler::get_rotationRay_Back() const {

// }

// void RotationHandler::set_rotationRay_Right(NodePath ray) {

// }

// NodePath RotationHandler::get_rotationRay_Right() const {

// }

// void RotationHandler::set_rotationRay_Left(NodePath ray) {

// }

// NodePath RotationHandler::get_rotationRay_Left() const {

// }

// void RotationHandler::set_rotationBody(NodePath rotbody) {

// }

// NodePath RotationHandler::get_rotationBody() const {

// }




