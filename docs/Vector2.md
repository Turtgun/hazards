# Vector2.hpp

This is a struct with two values, an X and a Y, I mostly use it for points in 2D space but you can find some clever uses for it.

## Operators

```cpp
Vector2 operator+(Vector2 otherVector){
    return Vector2(x + otherVector.x, y + otherVector.y);
}

Vector2 operator-(Vector2 otherVector){
    return Vector2(x - otherVector.x, y - otherVector.y);
}

Vector2 operator*(Vector2 otherVector){
    return Vector2(x * otherVector.x, y * otherVector.y);
}

Vector2 operator/(Vector2 otherVector){
    return Vector2(x / otherVector.x, y / otherVector.y);
}
```

This is how a vector interacts withanother vector when you just place a simple +, -, * or, / between them.

## Functions

### distanceTo

```cpp
inline double distanceTo(Vector2 otherVector) {
    double dx = otherVector.x-x;
    double dy = otherVector.y-y;
    return sqrt((dx*dx)+(dy*dy));
}
```

Finds the distance between this vector and another in 2D space.

### headingTo

```cpp
inline double headingTo(double currentHeading, Vector2 pointToFace) {
    Vector2 dvec = (pointToFace-*this);
    return std::atan2(dvec.y,dvec.x) - currentHeading;
}
```

Given a heading and a Vector2, find out much you need to turn (in radians) to get to a certain point if you were to start at this point.

### dotProduct

```cpp
inline double dotProduct(Vector2 otherVector) {
    return x*otherVector.x + y*otherVector.y;
}
```

Gives the dotProduct of this and another vector
