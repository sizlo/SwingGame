#include "CDemo.hpp"
#include "CSwingGame.hpp"
#include "CollisionHandler.hpp"
#include "SystemUtilities.hpp"
#include "DebugOptions.hpp"

CCircleShape * CreateCircleForPoint(CConvexShape &theShape, int thePoint)
{
    CCircleShape *circle = new CCircleShape(5.0f);
    circle->setFillColor(theShape.getFillColor());
    circle->setPosition(theShape.getPoint(thePoint) + theShape.getPosition());
    return circle;
}

CDemo::CDemo()
{
    mSpeed = 500.0f;

    float squareHalfWidth = 100.0f;

    std::list<CVector2f> points;
    points.push_back(CVector2f(-squareHalfWidth, -squareHalfWidth));
    points.push_back(CVector2f(squareHalfWidth, -squareHalfWidth));
    points.push_back(CVector2f(squareHalfWidth, squareHalfWidth));
    points.push_back(CVector2f(-squareHalfWidth, squareHalfWidth));

    mSquare = CConvexShape(points);
    mSquare.setPosition(800.0f, 500.0f);
    mSquare.setFillColor(CColour::Blue);

    points.clear();
    float triangleHalfWidth = 150.0f;
    float heightMultiplier = 0.5f;
    CVector2f top = CVector2f(0.0f, -triangleHalfWidth*heightMultiplier);
    CVector2f lowerRight = CVector2f(triangleHalfWidth, triangleHalfWidth*heightMultiplier);
    CVector2f lowerLeft = CVector2f(-triangleHalfWidth, triangleHalfWidth*heightMultiplier);
    points.push_back(top);
    points.push_back(lowerRight);
    points.push_back(lowerLeft);

    mTriangle = CConvexShape(points);
    mTriangle.setPosition(1000.0f, 650.0f);
    mTriangle.setFillColor(CColour::Green);

    mLowerLeftToTopDir = top - lowerLeft;
    mLowerRightToTopDir = top - lowerRight;
    mUpDir = CVector2f(0.0f, -1.0f);
    mLeftDir = CVector2f(-1.0f, 0.0f);
    mLowerLeftToTopDir.Normalise();
    mLowerRightToTopDir.Normalise();
    mUpDir.Normalise();
    mLeftDir.Normalise();

    mHorizontalAxis = CLine(CVector2f(600.0f, 1000.0f), CVector2f(1250.0f, 1000.0f));
    mVerticalAxis = CLine(CVector2f(100.0f, 300.0f), CVector2f(100.0f, 875.0f));

    CLine lowerLeftToTop = CLine(lowerLeft, top);
    CVector2f lowerLeftToTopNormal = lowerLeftToTop.GetNormal();
    CVector2f start = CVector2f(1600.0f, 700.0f);
    mRightDownAxis = CLine(start, start + (lowerLeftToTopNormal * 900.0f));

    CLine lowerRightToTop = CLine(lowerRight, top);
    CVector2f lowerRightToTopNormal = lowerRightToTop.GetNormal();
    start = CVector2f(400.0f, 500.0f);
    mRightUpAxis = CLine(start, start - (lowerRightToTopNormal * 500.0f));

    points.clear();
    points.push_back(mVerticalAxis.GetStart());
    points.push_back(mVerticalAxis.GetEnd());
    points.push_back(CVector2f(-500.0f, 500.0f));
    mVerticalAxisShape = CConvexShape(points);
    mVerticalAxisShape.setFillColor(CColour::Black);

    points.clear();
    points.push_back(mHorizontalAxis.GetStart());
    points.push_back(mHorizontalAxis.GetEnd());
    points.push_back(CVector2f(1000.0f, 2000.0f));
    mHorizontalAxisShape = CConvexShape(points);
    mHorizontalAxisShape.setFillColor(CColour::Black);

    points.clear();
    points.push_back(mRightDownAxis.GetStart());
    points.push_back(mRightDownAxis.GetEnd());
    points.push_back(CVector2f(3000.0f, -500.0f));
    mRightDownAxisShape = CConvexShape(points);
    mRightDownAxisShape.setFillColor(CColour::Black);

    points.clear();
    points.push_back(mRightUpAxis.GetStart());
    points.push_back(mRightUpAxis.GetEnd());
    points.push_back(CVector2f(-1000.0f, -500.0f));
    mRightUpAxisShape = CConvexShape(points);
    mRightUpAxisShape.setFillColor(CColour::Black);

    points.clear();
    points.push_back(CVector2f(100.0f, mSquare.getPosition().y - squareHalfWidth));
    points.push_back(CVector2f(100.0f, mSquare.getPosition().y + squareHalfWidth));
    points.push_back(CVector2f(110.0f, mSquare.getPosition().y + squareHalfWidth));
    points.push_back(CVector2f(110.0f, mSquare.getPosition().y - squareHalfWidth));
    mSquareVerticalProjection = CConvexShape(points);
    mSquareVerticalProjection.setFillColor(CColour(0, 0, 255, 0));

    points.clear();
    points.push_back(CVector2f(100.0f, mTriangle.getPosition().y - (triangleHalfWidth * 0.5f)));
    points.push_back(CVector2f(100.0f, mTriangle.getPosition().y + (triangleHalfWidth * 0.5f)));
    points.push_back(CVector2f(110.0f, mTriangle.getPosition().y + (triangleHalfWidth * 0.5f)));
    points.push_back(CVector2f(110.0f, mTriangle.getPosition().y - (triangleHalfWidth * 0.5f)));
    mTriangleVerticalProjection = CConvexShape(points);
    mTriangleVerticalProjection.setFillColor(CColour(0, 255, 0, 0));

    points.clear();
    points.push_back(CVector2f(mSquare.getPosition().x - squareHalfWidth, 1000.0f));
    points.push_back(CVector2f(mSquare.getPosition().x + squareHalfWidth, 1000.0f));
    points.push_back(CVector2f(mSquare.getPosition().x + squareHalfWidth, 990.0f));
    points.push_back(CVector2f(mSquare.getPosition().x - squareHalfWidth, 990.0f));
    mSquareHorizontalProjection = CConvexShape(points);
    mSquareHorizontalProjection.setFillColor(CColour(0, 0, 255, 0));

    points.clear();
    points.push_back(CVector2f(mTriangle.getPosition().x - triangleHalfWidth, 1000.0f));
    points.push_back(CVector2f(mTriangle.getPosition().x + triangleHalfWidth, 1000.0f));
    points.push_back(CVector2f(mTriangle.getPosition().x + triangleHalfWidth, 990.0f));
    points.push_back(CVector2f(mTriangle.getPosition().x - triangleHalfWidth, 990.0f));
    mTriangleHorizontalProjection = CConvexShape(points);
    mTriangleHorizontalProjection.setFillColor(CColour(0, 255, 0, 0));

    CVector2f squareLowerLeft = mSquare.getPoint(3) + mSquare.getPosition();
    CVector2f squareUpperRight = mSquare.getPoint(1) + mSquare.getPosition();
    CLine squareLowerLeftToRightUpAxisLine(squareLowerLeft, squareLowerLeft + mLowerRightToTopDir * 1000.0f);
    CLine squareUpperRightToRightUpAxisLine(squareUpperRight, squareUpperRight + mLowerRightToTopDir * 1000.0f);
    CVector2f squareLowerLeftRightUpIntersection;
    CVector2f squareUpperRightRightUpIntersection;
    squareLowerLeftToRightUpAxisLine.Intersects(mRightUpAxis, &squareLowerLeftRightUpIntersection);
    squareUpperRightToRightUpAxisLine.Intersects(mRightUpAxis, &squareUpperRightRightUpIntersection);
    CVector2f offset = squareLowerLeft - squareLowerLeftRightUpIntersection;
    offset.Normalise();
    offset *= 10.0f;
    points.clear();
    points.push_back(squareLowerLeftRightUpIntersection);
    points.push_back(squareUpperRightRightUpIntersection);
    points.push_back(squareUpperRightRightUpIntersection + offset);
    points.push_back(squareLowerLeftRightUpIntersection + offset);
    mSquareRightUpProjection = CConvexShape(points);
    mSquareRightUpProjection.setFillColor(CColour(0, 0, 255, 0));

    CVector2f triLowerLeft = lowerLeft + mTriangle.getPosition();
    CVector2f triLowerRight = lowerRight + mTriangle.getPosition();
    CLine triLowerLeftToRightUpAxisLine(triLowerLeft, triLowerLeft + mLowerRightToTopDir * 1000.0f);
    CLine triLowerRightToRightUpAxisLine(triLowerRight, triLowerRight + mLowerRightToTopDir * 1000.0f);
    CVector2f triLowerLeftRightUpIntersection;
    CVector2f triLowerRightRightUpIntersection;
    triLowerLeftToRightUpAxisLine.Intersects(mRightUpAxis, &triLowerLeftRightUpIntersection);
    triLowerRightToRightUpAxisLine.Intersects(mRightUpAxis, &triLowerRightRightUpIntersection);
    points.clear();
    points.push_back(triLowerLeftRightUpIntersection);
    points.push_back(triLowerRightRightUpIntersection);
    points.push_back(triLowerRightRightUpIntersection + offset);
    points.push_back(triLowerLeftRightUpIntersection + offset);
    mTriangleRightUpProjection = CConvexShape(points);
    mTriangleRightUpProjection.setFillColor(CColour(0, 255, 0, 0));

    CVector2f squareUpperLeft = mSquare.getPoint(0) + mSquare.getPosition();
    CVector2f squareLowerRight = mSquare.getPoint(2) + mSquare.getPosition();
    CLine squareUpperLeftToRightDownAxisLine(squareUpperLeft, squareUpperLeft + mLowerLeftToTopDir * 1000.0f);
    CLine squareLowerRightToRightDownAxisLine(squareLowerRight, squareLowerRight + mLowerLeftToTopDir * 1000.0f);
    CVector2f squareUpperLeftRightDownIntersection;
    CVector2f squareLowerRightRightDownIntersection;
    squareUpperLeftToRightDownAxisLine.Intersects(mRightDownAxis, &squareUpperLeftRightDownIntersection);
    squareLowerRightToRightDownAxisLine.Intersects(mRightDownAxis, &squareLowerRightRightDownIntersection);
    offset = squareUpperLeft - squareUpperLeftRightDownIntersection;
    offset.Normalise();
    offset *= 10.0f;
    points.clear();
    points.push_back(squareUpperLeftRightDownIntersection);
    points.push_back(squareLowerRightRightDownIntersection);
    points.push_back(squareLowerRightRightDownIntersection + offset);
    points.push_back(squareUpperLeftRightDownIntersection + offset);
    mSquareRightDownProjection = CConvexShape(points);
    mSquareRightDownProjection.setFillColor(CColour(0, 0, 255, 0));

    CLine triLowerLeftToRightDownAxisLine(triLowerLeft, triLowerLeft + mLowerLeftToTopDir * 1000.0f);
    CLine triLowerRightToRightDownAxisLine(triLowerRight, triLowerRight + mLowerLeftToTopDir * 1000.0f);
    CVector2f triLowerLeftRightDownIntersection;
    CVector2f triLowerRightRightDownIntersection;
    triLowerLeftToRightDownAxisLine.Intersects(mRightDownAxis, &triLowerLeftRightDownIntersection);
    triLowerRightToRightDownAxisLine.Intersects(mRightDownAxis, &triLowerRightRightDownIntersection);
    points.clear();
    points.push_back(triLowerLeftRightDownIntersection);
    points.push_back(triLowerRightRightDownIntersection);
    points.push_back(triLowerRightRightDownIntersection + offset);
    points.push_back(triLowerLeftRightDownIntersection + offset);
    mTriangleRightDownProjection = CConvexShape(points);
    mTriangleRightDownProjection.setFillColor(CColour(0, 255, 0, 0));
}

CDemo::~CDemo()
{
    ClearPointList();
}

void CDemo::Enter()
{
    CSwingGame::RegisterRenderable(this);
    CSwingGame::RegisterUpdateable(this);

    mState = kStart;
}

void CDemo::Exit()
{
    CSwingGame::UnregisterRenderable(this);
    CSwingGame::UnregisterUpdateable(this);
}

void CDemo::Update(CTime elapsedTime)
{
    CConvexShape collidingShape;
    switch (mState)
    {
    case kProjectingFirstPoint:
    case kProjectingSquareToVertical:
    case kProjectingTriangleToVertical:
        collidingShape = mVerticalAxisShape;
        break;

    case kProjectingSquareToHorizontal:
    case kProjectingTriangleToHorizontal:
        collidingShape = mHorizontalAxisShape;
        break;

    case kProjectingSquareToRightUp:
    case kProjectingTriangleToRightUp:
        collidingShape = mRightUpAxisShape;
        break;

    case kProjectingSquareToRightDown:
    case kProjectingTriangleToRightDown:
        collidingShape = mRightDownAxisShape;
    }

    for (ProjectionPoint *point: mProjectionPoints)
    {
        CCircleShape *circle = point->shape;
        CVector2f cv;
        if (!CollisionHandler::AreColliding(*circle, collidingShape, &cv))
        {
            circle->move(point->direction * elapsedTime.asSeconds() * mSpeed);
        }
        else
        {
            circle->move(cv);
            point->direction = CVector2f(0.0f, 0.0f);
        }
    }

    if (SystemUtilities::WasKeyPressedThisCycle(CKeyboard::Space))
    {
        AdvanceState();
    }
}

void CDemo::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mSquare);
    theWindow->DrawShape(mTriangle);

    theWindow->DrawLine(mHorizontalAxis, CColour::Black);
    theWindow->DrawLine(mVerticalAxis, CColour::Black);
    theWindow->DrawLine(mRightDownAxis, CColour::Black);
    theWindow->DrawLine(mRightUpAxis, CColour::Black);

    for (ProjectionPoint *point: mProjectionPoints)
    {
        theWindow->DrawShape(*(point->shape));
    }

    theWindow->draw(mSquareVerticalProjection);
    theWindow->draw(mSquareHorizontalProjection);
    theWindow->draw(mSquareRightDownProjection);
    theWindow->draw(mSquareRightUpProjection);
    theWindow->draw(mTriangleVerticalProjection);
    theWindow->draw(mTriangleHorizontalProjection);
    theWindow->draw(mTriangleRightDownProjection);
    theWindow->draw(mTriangleRightUpProjection);

    if (DebugOptions::showMouseCoords)
    {
        theWindow->DrawShape(mVerticalAxisShape);
        theWindow->DrawShape(mHorizontalAxisShape);
        theWindow->DrawShape(mRightDownAxisShape);
        theWindow->DrawShape(mRightUpAxisShape);
    }
}

void CDemo::AdvanceState()
{
    mState++;
    if (mState >= kMaxState)
    {
        CSwingGame::GoToLocation(kGameLocationDemo);
        return;
    }

    ProjectionPoint *p = NULL;

    switch (mState)
    {
    case kStart:
        break;

    case kProjectingFirstPoint:
        p = new ProjectionPoint();
        p->shape = CreateCircleForPoint(mSquare, 0);
        p->direction = mLeftDir;
        mProjectionPoints.push_back(p);
        break;

    case kProjectingSquareToVertical:
        for (int i = 1; i < 4; i++)
        {
            p = new ProjectionPoint();
            p->shape = CreateCircleForPoint(mSquare, i);
            p->direction = mLeftDir;
            mProjectionPoints.push_back(p);
        }
        break;

    case kShowSquareVerticalProjection:
        ClearPointList();
        mSquareVerticalProjection.setFillColor(CColour(0, 0, 255, 128));
        break;

    case kProjectingTriangleToVertical:
        for (int i = 0; i < 3; i++)
        {
            p = new ProjectionPoint();
            p->shape = CreateCircleForPoint(mTriangle, i);
            p->direction = mLeftDir;
            mProjectionPoints.push_back(p);
        }
        break;

    case kShowTriangleVerticalProjection:
        ClearPointList();
        mTriangleVerticalProjection.setFillColor(CColour(0, 255, 0, 128));
        break;

    case kProjectingSquareToHorizontal:
        for (int i = 0; i < 4; i++)
        {
            p = new ProjectionPoint();
            p->shape = CreateCircleForPoint(mSquare, i);
            p->direction = -mUpDir;
            mProjectionPoints.push_back(p);
        }
        break;

    case kShowSquareHorizontalProjection:
        ClearPointList();
        mSquareHorizontalProjection.setFillColor(CColour(0, 0, 255, 128));
        break;

    case kProjectingTriangleToHorizontal:
        for (int i = 0; i < 3; i++)
        {
            p = new ProjectionPoint();
            p->shape = CreateCircleForPoint(mTriangle, i);
            p->direction = -mUpDir;
            mProjectionPoints.push_back(p);
        }
        break;

    case kShowTriangleHorizontalProjection:
        ClearPointList();
        mTriangleHorizontalProjection.setFillColor(CColour(0, 255, 0, 128));
        break;

    case kProjectingSquareToRightUp:
        for (int i = 0; i < 4; i++)
        {
            p = new ProjectionPoint();
            p->shape = CreateCircleForPoint(mSquare, i);
            p->direction = mLowerRightToTopDir;
            mProjectionPoints.push_back(p);
        }
        break;

    case kShowSquareRightUpProjection:
        ClearPointList();
        mSquareRightUpProjection.setFillColor(CColour(0, 0, 255, 128));
        break;

    case kProjectingTriangleToRightUp:
        for (int i = 0; i < 3; i++)
        {
            p = new ProjectionPoint();
            p->shape = CreateCircleForPoint(mTriangle, i);
            p->direction = mLowerRightToTopDir;
            mProjectionPoints.push_back(p);
        }
        break;

    case kShowTriangleRightUpProjection:
        ClearPointList();
        mTriangleRightUpProjection.setFillColor(CColour(0, 255, 0, 128));
        break;

    case kProjectingSquareToRightDown:
        for (int i = 0; i < 4; i++)
        {
            p = new ProjectionPoint();
            p->shape = CreateCircleForPoint(mSquare, i);
            p->direction = mLowerLeftToTopDir;
            mProjectionPoints.push_back(p);
        }
        break;

    case kShowSquareRightDownProjection:
        ClearPointList();
        mSquareRightDownProjection.setFillColor(CColour(0, 0, 255, 128));
        break;

    case kProjectingTriangleToRightDown:
        for (int i = 0; i < 3; i++)
        {
            p = new ProjectionPoint();
            p->shape = CreateCircleForPoint(mTriangle, i);
            p->direction = mLowerLeftToTopDir;
            mProjectionPoints.push_back(p);
        }
        break;

    case kShowTriangleRightDownProjection:
        ClearPointList();
        mTriangleRightDownProjection.setFillColor(CColour(0, 255, 0, 128));
        break;

    default:
        break;
    }
}

void CDemo::ClearPointList()
{
    while (!mProjectionPoints.empty())
    {
        ProjectionPoint *removed = mProjectionPoints.front();
        mProjectionPoints.pop_front();
        SAFE_DELETE(removed->shape);
        SAFE_DELETE(removed);
    }
}