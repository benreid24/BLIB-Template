#include <BLIB/Cameras/2D/Camera2D.hpp>
#include <BLIB/Engine.hpp>
#include <BLIB/Graphics.hpp>
#include <BLIB/Logging.hpp>
#include <Properties.hpp>

class DemoEngineState : public bl::engine::State {
public:
    static constexpr float DegPerSec = 90.f;

    static bl::engine::State::Ptr create() { return Ptr(new DemoEngineState()); }

    virtual const char* name() const { return "DemoEngineState"; }

    virtual void activate(bl::engine::Engine& engine) {
        auto scene = engine.renderer().getObserver().pushScene<bl::rc::scene::Scene2D>();
        engine.renderer().getObserver().setCamera<bl::cam::Camera2D>(glm::vec2(400, 300),
                                                                     glm::vec2(800, 600));
        engine.renderer().getObserver().setClearColor(bl::sfcol(sf::Color::Cyan));

        triangle.create(engine, {0.f, 173.f}, {200.f, 173.f}, {100.f, 0.f});
        triangle.setColorGradient({1.f, 0.f, 0.f, 1.f}, {0.f, 1.f, 0.f, 1.f}, {0.f, 0.f, 1.f, 1.f});
        triangle.getTransform().setPosition(400.f, 300.f);
        triangle.getTransform().setOrigin({100.f, 123.f});
        triangle.addToScene(scene, bl::rc::UpdateSpeed::Dynamic);

        BL_LOG_INFO << "DemoEngineState activated";
    }

    virtual void deactivate(bl::engine::Engine& engine) override {
        engine.renderer().getObserver().popScene();
    }

    virtual void update(bl::engine::Engine&, float dt, float) override {
        triangle.getTransform().rotate(dt * DegPerSec);
    }

private:
    bl::gfx::Triangle triangle;

    DemoEngineState()
    : State(bl::engine::StateMask::Running) {}
};

int main() {
    BL_LOG_INFO << "Loading application properties";
    if (!Properties::load()) {
        BL_LOG_ERROR << "Failed to load application properties";
        return 1;
    }

    BL_LOG_INFO << "Creating engine instance";
    const bl::engine::Settings engineSettings =
        bl::engine::Settings()
            .withWindowParameters(
                bl::engine::Settings::WindowParameters()
                    .withVideoMode(sf::VideoMode(800, 600, 32))
                    .withStyle(sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize)
                    .withTitle("BLIB Project")
                    .withLetterBoxOnResize(true)
                    .fromConfig())
            .fromConfig();
    bl::engine::Engine engine(engineSettings);
    BL_LOG_INFO << "Created engine";

    BL_LOG_INFO << "Running engine main loop";
    if (!engine.run(DemoEngineState::create())) {
        BL_LOG_ERROR << "Engine exited with error";
        return 1;
    }

    BL_LOG_INFO << "Exiting normally";
    return 0;
}
