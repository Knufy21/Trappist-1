#pragma once

#include <Trappist-1\ui\actions\Action.hpp>

namespace ui
{
	// Action-Klasse zum Interpolieren auf eine bestimmte 'Color' eines 'Control's.
	class CircleAction : public Action
	{
	public:
		enum Type { AROUND_POINT_TO, AROUND_POINT_BY };

		// Erstellt eine 'CircleAction'-Instanz, wobei die Margin(middlePoint) in der Zeit(duration) in Sekunden mit der Interpolation(interpolation) auf das Zielobjekt übertragen wird.
		CircleAction(Type type, const glm::vec2 &middlePoint, float degrees, float duration, const Interpolation &interpolation = Interpolation::linear);

		// Destruktor
		~CircleAction();

		// Gibt einen Zeiger auf die auf dem Heap neu kopierte Instanz zurück.
		virtual Action* clone() const override;
	protected:
		// Eventfunktion, die aufgerufen wird, sobald das Zielobjekt geändert wurde.
		void onTargetChanged() override;

		// Wendet den Farb-Status des Ziels für die Prozentzahl(percent) im Wertebereich 0 bis 1 an.
		void apply(float percent) override;

		// Typ, der bestimmt, welche Werte wie verändert werden.
		const Type type;

		// Wert des Prozentstatus 0.
		glm::vec2 startValue;
		double startDegrees;

		// Wert des Prozentstatus 1.
		//Margin endValue;
		//float endDegrees;

		// Eingabewert.
		const glm::vec2 inputValue;
		const float degrees;
	};
}