#pragma once

#include <functional>
#include <glm\glm.hpp>
#include <Trappist-1\UI\Interpolation.hpp>

namespace ui
{
	class Widget;

	// Basisklasse zum Interpolieren von Eigenschaften eines 'Widget's.
	class Action
	{
	public:
		// Erstellt eine 'Action'-Instanz, mit der Zeit(duration) in Sekunden und der Interpolation(interpolation).
		Action(float duration, const Interpolation &interpolation);

		// Virtueller Destruktor.
		virtual ~Action();

		// Gibt einen Zeiger auf die auf dem Heap neu kopierte Instanz zurück.
		virtual Action* clone() const = 0;

		// Aktualisiert das Objekt mit der Zeit in Sekunden, die seit dem letzten Frame vergangen ist.
		void update(float deltaTime);

		// Returns whether the action has finished or not.
		bool hasFinished() const;

		// Getter des Zielobjekt.
		const Widget &getTarget() const;

		// Setter des Zielobjekt.
		void setTarget(Widget &target);

		// Setzt eine Funktion, die aufgerufen wird, sobald der Prozentstatus 1 erreicht wurde.
		void setFinishListener(std::function<void()> listener);
	protected:
		// Eventfunktion, die aufgerufen wird, sobald das Zielobjekt geändert wurde.
		virtual void onTargetChanged() = 0;

		// Wendet den Farb-Status des Ziels für die Prozentzahl(percent) im Wertebereich 0 bis 1 an.
		virtual void apply(float percent) = 0;

		// Die vergangene Zeit in Sekunden seit des Startes.
		float currTime;

		// Die Zeit in Sekunden, die der Vorgang laufen soll.
		const float duration;

		// Zeiger auf das 'Widget', für das die Einstellungen vernommen werden sollen.
		Widget *target;

		// Referenz auf ein statischen Member der 'Interpolation'-Klasse, die zum Verändern der Prozentzahl für die 'apply'-Funktion benutzt wird.
		const Interpolation &interpolation;

		// Gibt an, ob der Prozentstatus 1 erreicht wurde.
		bool finished;
	private:
		// Funktion, die aufgerufen wird, sobald der Prozentstatus 1 erreicht wurde.
		std::function<void()> onFinish;
	};
}