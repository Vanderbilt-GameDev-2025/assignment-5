// #ifndef BODYROTATION_HANDLER_H
// #define BODYROTATION_HANDLER_H

// #include <godot_cpp/classes/node3d.hpp>
// #include <godot_cpp/classes/node.hpp>
// #include <godot_cpp/variant/node_path.hpp>
// #include <godot_cpp/classes/marker3d.hpp>
// #include <godot_cpp/core/class_db.hpp>

// namespace godot {

// class RotationHandler : public Node3D {
//     GDCLASS(RotationHandler, Node3D);

// private:

//     bool handlerReady;
//     bool rotatingXaxis;
//     bool rotatingZaxis;

//     float checkerCooldown;
//     float checkTime;

//     NodePath rotationRay_Front;
//     NodePath rotationRay_Back;
//     NodePath rotationRay_Right;
//     NodePath rotationRay_Left;
//     NodePath rotationBody;

//     std::array<NodePath, 4> rotationRay_array;

// protected:

//     static void _bind_methods();

// public:

//     void _ready() override;
//     void _process(double delta) override; //If !handlerReady, validate rays + return. If handler is ready, check rotations
//     void validateRays(); //go through each of the rays in the ray array. If any are empty, set readyFlag to false
//     void checkRotation(); //If the y value of the rotation ray's hit point is greater than or less than the y value of the rotation ray's hit point
//     //on the opposite side, then a rotation is needed to be made. 
//     void rotateXaxis(double delta);
//     void rotateZaxis(double delta);
//     void startCooldown(); //checkerCooldown = 0

//     bool is_Ready();
//     void set_readyFlag(bool flag);

//     void set_checkTime(float time);
//     float get_checkTime() const;

//     void set_rotationRay_Front(NodePath ray);
//     NodePath get_rotationRay_Front() const;

//     void set_rotationRay_Back(NodePath ray);
//     NodePath get_rotationRay_Back() const;

//     void set_rotationRay_Right(NodePath ray);
//     NodePath get_rotationRay_Right() const;

//     void set_rotationRay_Left(NodePath ray);
//     NodePath get_rotationRay_Left() const;

//     void set_rotationBody(NodePath rotBody);
//     NodePath get_rotationBody() const;



// };

// }

// #endif // BODYROTATION_HANDLER_H