#include "CGameLocation.hpp"
#include "CUpdateable.hpp"
#include "CRenderable.hpp"

enum EDemoState
{
    kStart,
    kShowNormals,
    kShowVerticalAxis,
    kShowHorizontalAxis,
    kShowRightUpAxis,
    kShowRightDownAxis,
    kHideNormals,
    kProjectingFirstPoint,
    kProjectingSquareToVertical,
    kShowSquareVerticalProjection,
    kProjectingTriangleToVertical,
    kShowTriangleVerticalProjection,
    kProjectingSquareToHorizontal,
    kShowSquareHorizontalProjection,
    kProjectingTriangleToHorizontal,
    kShowTriangleHorizontalProjection,
    kProjectingSquareToRightUp,
    kShowSquareRightUpProjection,
    kProjectingTriangleToRightUp,
    kShowTriangleRightUpProjection,
    kProjectingSquareToRightDown,
    kShowSquareRightDownProjection,
    kProjectingTriangleToRightDown,
    kShowTriangleRightDownProjection,
    kAnimateToCollision,
    kMaxState
};

struct ProjectionPoint
{
    CCircleShape *shape;
    CVector2f direction;
};

class CDemo : public CGameLocation, public CRenderable, public CUpdateable
{
public:
    CDemo();
    ~CDemo();

    void Enter();
    void Exit();

    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);

    void AdvanceState();
    void ClearPointList();
    void ClearNormalHighlights();

    void MoveTriangle(CVector2f offset);

private:
    CConvexShape mSquare;
    CConvexShape mTriangle;

    CVector2f mUpDir;
    CVector2f mLeftDir;
    CVector2f mLowerLeftToTopDir;
    CVector2f mLowerRightToTopDir;

    CLine mHorizontalAxis;
    CLine mVerticalAxis;
    CLine mRightDownAxis;
    CLine mRightUpAxis;

    CConvexShape mHorizontalAxisShape;
    CConvexShape mVerticalAxisShape;
    CConvexShape mRightDownAxisShape;
    CConvexShape mRightUpAxisShape;

    CColour mHorizontalAxisColour;
    CColour mVerticalAxisColour;
    CColour mRightDownAxisColour;
    CColour mRightUpAxisColour;

    CConvexShape mSquareVerticalProjection;
    CConvexShape mSquareHorizontalProjection;
    CConvexShape mSquareRightDownProjection;
    CConvexShape mSquareRightUpProjection;

    CConvexShape mTriangleVerticalProjection;
    CConvexShape mTriangleHorizontalProjection;
    CConvexShape mTriangleRightDownProjection;
    CConvexShape mTriangleRightUpProjection;

    int mState;

    float mSpeed;
    CTime mAnimationTime;

    std::list<ProjectionPoint *> mProjectionPoints;
    std::list<CCircleShape *> mNormalHighlights;
};