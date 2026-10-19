# Language Policy (QExt)

> Scope: ALL code, comments, commit messages, and documentation inside the QExt repository.
> AI session interaction with the user may use Chinese; everything that lands in the repo MUST be English.

## Rule

1. **Code comments / CMake comments**: English only.
2. **Commit messages**: English only (subject + body).
3. **Docs** (`docs/`, `README.md`, `*.md` under source dirs): English only.
4. **`.agents/memorys/`**: Chinese allowed (session memory for AI interaction, per project convention).
5. **Pre-existing Chinese comments** (e.g. `src/qmls/quick/controls/tests/CMakeLists.txt:43`): do NOT bulk-rewrite history; fix them only when the surrounding code is being touched anyway.

## Enforcement check

```bash
# Chinese characters in build files / sources (must be 0 outside .agents/):
grep -rn '[一-龥]' --include='*.cmake' --include='CMakeLists.txt' --include='*.h' --include='*.cpp' cmake/ CMakeLists.txt src/ | wc -l
# Commit message check (subject line):
git log --format='%s' -20 | grep -P '[\x{4e00}-\x{9fff}]' || echo OK
```

Blocking condition: any new (non-.agents) file content containing CJK characters must not be committed.

First precedent: 2026-10-19 cross-build batch (RELOCATE/qmldump changes) originally carried Chinese comments; translated to English before commit per user directive.
