	•	Clinic Management:
	•	Supports three clinics (Heart, Pulmonary, Plastic Surgery).
	•	Each clinic maintains a queue of up to 10 patients (both regular and critical).
	•	Uses custom queue and linked-list structures
	•	Patient Operations:
	•	Add regular or critically ill patients.
	•	Remove patients for operations (critical first).
	•	Cancel patients by SSN with validation and error logs.
	•	View all current patients in a department.
	•	File I/O & Validation:
	•	Reads initial patient list from patient.csv.
	•	Logs all successful and failed transactions to a separate file.
	•	Detects and reports invalid data (bad SSNs, full queues, or invalid clinic names).
	•	Data Structures:
	•	Patient struct storing name, SSN, and status.
	•	Clinic class handling queue operations and logging.
	•	Modular .h and .cpp files for clean organization.



 Planned 

(These are the parts you’re adding next, so keep them as “planned” — you can change them to “implemented” later.)
	•	Ambulance Tracking System:
Track ambulance dispatches, routes, and arrivals for each clinic.
	•	Room Allocation:
Assign patients to available rooms dynamically and record availability by department.
	•	Feedback Sentiment Analysis:
Collect daily patient feedback, analyze tone using sentiment scoring, and attach reports to each clinic.
	•	Daily Summary Reports:
Combine patient data and sentiment analysis to produce an end-of-day operational summary.
