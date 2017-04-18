#pragma once

#include <Trappist-1\ui\actions\Action.hpp>

namespace ui
{
	// Action-Klasse zum Interpolieren auf oder um eines bestimmten 'vec3'-Wertes eines 'Widget's.
	class Vec3Action : public Action
	{
		typedef glm::vec3 T;
	public:
		enum Type : unsigned char { RGB_TO, RGB_BY };

		// Erstellt eine 'Vec3Action'-Instanz, wobei der Wert(value) in der Zeit(duration) in Sekunden mit der Interpolation(interpolation) durch den Typ(type) auf das Zielobjekt �bertragen wird.
		Vec3Action(Type type, const T &value, float duration, const Interpolation &interpolation = Interpolation::linear, std::function<void()> onFinish = nullptr);

		// Erstellt eine 'Vec3Action'-Instanz, wobei der Wert(value) in der Zeit(duration) in Sekunden mit der Interpolation(interpolation) durch den Typ(type) auf das Zielobjekt �bertragen wird.
		Vec3Action(Type type, const T &value, float duration, std::function<void()> onFinish, const Interpolation &interpolation = Interpolation::linear);

		// Destruktor
		~Vec3Action();

		// Gibt einen 'Action'-Zeiger auf die auf dem Heap neu kopierte Instanz zur�ck.
		virtual Action* clone() const override;
	protected:
		// Eventfunktion, die aufgerufen wird, sobald das Zielobjekt ge�ndert wurde.
		void onTargetChanged() override;

		// Wendet den 'Vector3f'-Status des Ziels f�r die Prozentzahl(percent) im Wertebereich 0 bis 1 an.
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