#pragma once

namespace Hyve::Runtime {
	struct HObject;
	struct HVariable;

	enum class ReferenceType {
		STRONG,
		WEAK
	};

	struct Reference {
		// Where this reference comes from
		HObject* From;
		// Where this reference goes to
		HObject* To;
		// The type of reference
		ReferenceType Type;
	};

	struct RootReference {
		HVariable* Variable;
		HObject* Object;
	};
}