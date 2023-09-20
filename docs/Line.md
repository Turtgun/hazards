# Line.hpp

The line class takes in 2 [Vector2](Vector2.md)s (startPos and endPos) and makes a imaginary line between them

## dvec

This is the delta vector between the two positions.

```cpp
dvec = endPos-startPos;
```

## disBtwnCords

```cpp
disBtwnCords = startPos.distanceTo(endPos);
```

The distance between the two points.

## Functions

### ratioToCoordinate

```cpp
Vector2 ratioToCoordinate(double ratio){
    return Vector2(dvec.x * ratio + startPos.x, dvec.y * ratio + startPos.y);
}
```

Given a ratio between 0 and 1 it returns a point inside of the line, starting from startPos, depending on the ratio given.
