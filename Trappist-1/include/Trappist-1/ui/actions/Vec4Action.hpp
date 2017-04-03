#pragma once

#include <Trappist-1\ui\actions\Action.hpp>

namespace ui
{
	// Action-Klasse zum Interpolieren auf oder um eines bestimmten 'vec4'-Wertes eines 'Widget's.
	class Vec4Action : public Action
	{
		typedef glm::vec4 T;
	public:
		enum class Type : unsigned char { RGBA_TO, RGBA_BY, TEXT_RGBA_TO, TEXT_RGBA_BY, TEXT_OUTLINE_RGBA_TO, TEXT_OUTLINE_RGBA_BY };

		// Erstellt eine 'Vec4Action'-Instanz, wobei der Wert(value) in der Zeit(duration) in Sekunden mit der Interpolation(interpolation) durch den Typ(type) auf das Zielobjekt übertragen wird.
		Vec4Action(Type type, const T &value, float duration, const Interpolation &interpolation = Interpolation::linear);

		// Destruktor
		~Vec4Action();

		// Gibt einen 'Action'-Zeiger auf die auf dem Heap neu kopierte Instanz zurück.
		virtual Action* clone() const override;
	protected:
		// Eventfunktion, die aufgerufen wird, sobald das Zielobjekt geändert wurde.
		void onTargetChanged() override;

		// Wendet den 'Vector4f'-Status des Ziels für die Prozentzahl(percent) im Wertebereich 0 bis 1 an.
		void apply(float percent) override;

		// Typ, der bestimmt, welche Werte wie verändert werden.
		const Type type;

		// Wert des Prozentstatus 0.
		T startValue;

		// Wert des Prozentstatus 1.
		T endValue;

		// Eingabewert.
		const T inputValue;
	};
}