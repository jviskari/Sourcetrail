#ifndef DEFINITION_KIND_H
#define DEFINITION_KIND_H

enum DefinitionKind
{	 // these values are stored in the database, do not reorder
	DEFINITION_NONE = 0,
	DEFINITION_IMPLICIT = 1,
	DEFINITION_EXPLICIT = 2
};

int definitionKindToInt(DefinitionKind definitionKind);
DefinitionKind intToDefinitionKind(int definitionKind);

#endif	  // DEFINITION_TYPE_H
