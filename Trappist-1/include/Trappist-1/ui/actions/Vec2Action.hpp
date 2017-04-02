#pragma once

#include <Trappist-1\ui\actions\Action.hpp>

namespace ui
{
	// Action-Klasse zum Interpolieren auf oder um eines bestimmten 'vec2'-Wertes eines 'Control's.
	class Vec2Action : public Action
	{
		typedef glm::vec2 T;
	public:
		enum Type : unsigned char { MOVE_TO, MOVE_BY, SIZE_TO, SIZE_BY, SCALE_TO, SCALE_BY };

		// Erstellt eine 'Vec2Action'-Instanz, wobei der Wert(value) in der Zeit(duration) in Sekunden mit der Interpolation(interpolation) durch den Typ(type) auf das Zielobjekt �bertragen wird.
		Vec2Action(Type type, const T &value, float duration, const Interpolation &interpolation = Interpolation::linear);

		// Destruktor
		~Vec2Action();

		// Gibt einen 'Action'-Zeiger auf die auf dem Heap neu kopierte Instanz zur�ck.
		virtual Action* clone() const override;
	protected:
		// Eventfunktion, die aufgerufen wird, sobald das Zielobjekt ge�ndert wurde.
		void onTargetChanged() override;

		// Wendet den 'Vector2f'-Status des Ziels f�r die Prozentzahl(percent) im Wertebereich 0 bis 1 an.
		void apply(float percent) override;

		// Typ, der bestimmt, welche Werte wie ver�ndert werden.
		const Type type;

		// Wert des Prozentstatus 0.
		T startValue;

		// Wert des Prozentstatus 1.
		T endValue;

		// Eingabewert.
		const T inputValue;
	};
}