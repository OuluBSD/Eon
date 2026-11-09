# CodeGen Package AGENTS Guide

## Scope
- Applies to `uppsrc/CodeGen` and its entire sub-tree of U++ packages.

## Purpose
- Code generation utilities for U++ applications
- Provides tools for generating source code, bindings, and infrastructure
- Supports multiple output formats and target languages
- Integrates with other U++ packages for code generation workflows

## Key Areas
- **Code Generator**: Main code generation engine
- **Template System**: Template-based code generation with placeholders
- **Output Formats**: Support for various code formats and languages
- **Binding Generation**: Automatic binding generation for interop
- **Infrastructure Code**: Generation of boilerplate and utility code
- **Plugin System**: Extensible plugin architecture for custom generators

## Extension Points
- Add new generator behavior through the `CodeGenApp` editor (`Editor.h/.cpp`) and its `Parser.cpp` template processing
- Implement custom templates with specialized placeholders
- Extend output formats with new code styles and conventions
- Add new binding types for interop with external systems
- Integrate with external code generation tools

## Conventions
- Follow `/CODESTYLE.md` for code style and documentation
- Use proper U++ naming conventions (PascalCase for classes, camelCase for methods)
- Include `AGENTS.md` as first file in `.upp` manifest
- Document all public APIs with Topic++ (`.tpp`) style comments
- Use `Separate` and `ReadOnly` options in `.upp` for logical grouping
- Keep package header (`AGENTS.md`) up to date with any structural changes
- Use proper acronym casing for shared components
- Prefer shared implementations over duplicated code patterns
- Follow existing patterns in the codebase

- Follow repo-wide naming rules: `ai/rules/naming-conventions.md`

## Dependencies
- Core: Basic U++ functionality
- Common: Shared utilities and base classes
- TheIDE: Integration with the IDE application
- Common: Shared utilities and base classes

## Where To Start
- Review `CodeGen.h` — the package umbrella that includes `Editor.h`
- Study `CodeGenApp` (`Editor.h/.cpp`) — the main generator/editor window
- Examine `Parser.cpp` for template parsing
- Check the template files `base.cg` and `interfaces.tg`

## Design Principles
- Clean separation between code generation logic and output formatting
- Extensible architecture for new generators and templates
- Consistent API design for code generation operations
- Comprehensive error handling and reporting
- Efficient template processing for large codebases

