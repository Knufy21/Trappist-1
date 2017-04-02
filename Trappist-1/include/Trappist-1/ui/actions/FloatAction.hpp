#pragma once

#include <Trappist-1\ui\actions\Action.hpp>

namespace ui
{
	// Action-Klasse zum Interpolieren auf oder um eines bestimmten Gleitkommazahlenwertes eines 'Control's.
	class FloatAction : public Action
	{
		typedef float T;
	public:
		enum Type { ALPHA_TO, ALPHA_BY, ROTATE_TO, ROTATE_BY };

		// Erstellt eine 'FloatAction'-Instanz, wobei der Wert(value) in der Zeit(duration) in Sekunden mit der Interpolation(interpolation) durch den Typ(type) auf das Zielobjekt �bertragen wird.
		FloatAction(Type type, T value, float duration, const Interpolation &interpolation = Interpolation::linear);

		// Destruktor
		~FloatAction();

		// Gibt einen 'Action'-Zeiger auf die auf dem Heap neu kopierte Instanz zur�ck.
		virtual Action* clone() const override;
	protected:
		// Eventfunktion, die aufgerufen wird, sobald das Zielobjekt ge�ndert wurde.
		void onTargetChanged() override;

		// Wendet den Float-Status des Ziels f�r die Prozentzahl(percent) im Wertebereich 0 bis 1 an.
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