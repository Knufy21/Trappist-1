#pragma once

#include <glm\glm.hpp>
#include <Trappist-1\graphics\Rect.hpp>

class Transform2D
{
public:
	// Constructs a transform using the specified or default position, rotation, scalar and origin.
	Transform2D(const glm::vec2 &position = glm::vec2(0.0f, 0.0f), float rotation = 0.0f, const glm::vec2 &scalar = glm::vec2(1.0f, 1.0f), const glm::vec2 &origin = glm::vec2(0.0f, 0.0f));

	virtual ~Transform2D();

	// Returns the matrix of this transform.
	const glm::mat3 &getTransform() const;

	// Sets the position of the transform to the specified value.
	void setPosition(float x, float y);

	// Sets the position of the transform to the specified value.
	void setPosition(const glm::vec2 &position);

	// Translates the transform by the specified offset.
	void translate(float offsetX, float offsetY);

	// Translates the transform by the specified offset.
	void translate(const glm::vec2 &offset);

	// Sets the origin of the transform to the specified value.
	void setOrigin(float originX, float originY);

	// Sets the origin of the transform to the specified value.
	void setOrigin(const glm::vec2 &origin);

	// Sets the rotation of the transform to the specified value.
	void setRotation(float rotation);

	// Rotates the transform by the specified angles in radians.
	void rotate(float angle);

	// Sets the scale of the transform to the specified factors.
	void setScale(float scalarX, float scalarY);

	// Sets the scale of the transform to the specified value.
	void setScale(const glm::vec2 &scalar);

	// Scales the transform by the specified factors.
	void scale(float factorX, float factorY);

	// Scales the transform by the specified factors.
	void scale(const glm::vec2 &factors);

	// Transformes a point with the transforms matrix.
	glm::vec2 transformPoint(float x, float y) const;

	// Transformes a point with the transforms matrix.
	glm::vec2 transformPoint(const glm::vec2 &point) const;

	// Transformes a rectangle with the transforms matrix.
	FloatRect transformRect(float left, float top, float width, float height) const;

	// Transformes a rectangle with the transforms matrix.
	FloatRect transformRect(const FloatRect &rect) const;

	// Returns the position of the transform.
	const glm::vec2 &getPosition() const;

	// Returns the origin of the transform.
	const glm::vec2 &getOrigin() const;

	// Returns the rotation of the transform.
	float getRotation() const;

	// Returns the scale of the transform.
	const glm::vec2 &getScale() const;

private:
	// Ensures whether the transform needs an update, and if so it is going to be updated.
	void ensureUpdate() const;

	// Determines whether any component of the transform have been changed and so the transform needs an update.
	mutable bool needsUpdate;

	// The matrix of the transoform.
	mutable glm::mat3 transform;

	// The position of the transform.
	glm::vec2 position;

	// The origin of the tranform.
	glm::vec2 origin;

	// The rotation of the transform specified in radians.
	float rotation;

	// The scalar of the transform.
	glm::vec2 scalar;
};

// Inline

inline const glm::vec2 &Transform2D::getPosition() const
{
	return this->position;
}

inline const glm::vec2 &Transform2D::getOrigin() const
{
	return this->origin;
}

inline float Transform2D::getRotation() const
{
	return this->rotation;
}

inline const glm::vec2 &Transform2D::getScale() const
{
	return this->scalar;
}