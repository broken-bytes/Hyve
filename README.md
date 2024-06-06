<p align="center">
  <img src="https://i.imgur.com/f7XHEDZ.png" style="height:250px;" />
</p>

# Hyve Programming Language
![Static Badge](https://img.shields.io/badge/C%2B%2B-20-purple) ![GitHub Release](https://img.shields.io/github/v/release/broken-bytes/Hyve?include_prereleases&sort=semver&label=version)
![GitHub branch check runs](https://img.shields.io/github/check-runs/broken-bytes/Hyve/main) 

## Overview
Hyve is a modern, highly asynchronous programming language designed for building scalable and efficient software. Embracing the latest in concurrent programming paradigms, Hyve offers a unique blend of performance, simplicity, and flexibility for developers.

## Features
- **Asynchronous by Nature**: At its core, Hyve is built to handle asynchronous operations seamlessly, making it ideal for IO-heavy tasks and high-load applications.
- **Modern Syntax**: Hyve's syntax is clean and expressive, enabling developers to write more code with fewer lines and clear readability.
- **Scalability**: Designed for scalability, Hyve can easily handle large-scale applications, from microservices to massive cloud-based systems.
- **Strong Typing with Inference**: Hyve offers strong typing capabilities with intelligent type inference, reducing boilerplate while maintaining type safety.
- **Cross-Platform Compatibility**: Write once, run anywhere. Hyve code is highly portable across various platforms.

## Installation
```bash
# Replace <version> with the desired version
curl -sSL https://hyve-lang.org/install.sh | sh -s -- <version>
```

## Quick Start
A simple "Hello, World!" in Hyve:

```hyve
class World {
    init {

    }

    func hello() -> String {
        "Hello World"
    }
}

async func main() {
    let world = World()
    print(world.hello());
}
```

## Documentation
Visit [Hyve Documentation](https://hyve-lang.org/docs) for detailed guides, API references, and tutorials.

## Community
- **GitHub**: [github.com/hyve-lang](https://github.com/broken-bytes/hyve)
- **Discord**: Join our [Hyve Discord Community](https://discord.gg/hyve-lang)
- **Twitter**: Follow us [@HyveLang](https://twitter.com/HyveLang) for updates and news.

## Contributing
We love contributions! If you're interested in contributing, please read our [Contributing Guide](https://github.com/hyve-lang/hyve/CONTRIBUTING.md).

## License
Hyve is open-sourced under the MIT License. See the [LICENSE](https://github.com/hyve-lang/hyve/LICENSE.md) file for details.

---

Happy Coding with Hyve!

Remember, since Hyve is a hobbyist language, expect missing features and bugs.
