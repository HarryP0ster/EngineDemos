#include "pch.hpp"
#include "engine.hpp"

GR::Entity sword;

void Loop(GR::GrayEngine* Context, double Delta)
{
	double angle = glm::mod(Context->GetTime(), 360.0);

	GRComponents::Transform& wld = Context->GetComponent<GRComponents::Transform>(sword);
	wld.SetOffset(TVec3(0.0, angle, 0.0));
	wld.SetRotation(0.0, glm::radians(angle * 50.0), 0.0);

	GRComponents::Color& clr = Context->GetComponent<GRComponents::Color>(sword);
	clr.RGB = glm::abs(TVec3(glm::sin(angle), glm::cos(angle), glm::tan(angle)));

	//glm::vec3 off = Context->GetMainCamera().View.GetOffset();
	//printf("%f %f %f\n", off.x, off.y, off.z);

	Context->GetWindow().SetTitle(("Vulkan Application " + std::format("{:.1f}", 1.0 / Delta)).c_str());
}

void KeyPress(GR::GrayEngine* Context, GR::EKey key, GR::EAction Action)
{
	if (Action == GR::EAction::Release)
		return;

	TVec3 off = TVec3(0.0);
	TVec3 rot = TVec3(0.0);

	switch (key)
	{
	case GR::EKey::A:
		off.x += 10.f;
		break;
	case GR::EKey::D:
		off.x -= 10.f;
		break;
	case GR::EKey::S:
		off.z -= 10.f;
		break;
	case GR::EKey::W:
		off.z += 10.f;
		break;
	case GR::EKey::ArrowRight:
		rot.y += 10.f;
		break;
	case GR::EKey::ArrowLeft:
		rot.y -= 10.f;
		break;
	case GR::EKey::ArrowDown:
		rot.x -= 10.f;
		break;
	case GR::EKey::ArrowUp:
		rot.x += 10.f;
		break;
	default:
		break;
	}

	rot = glm::radians(rot);
	Context->GetMainCamera().View.Rotate(rot.x, rot.y, rot.z);
	Context->GetMainCamera().View.Translate(off);
}

int main(int argc, char** argv)
{
	std::string exec_path = "";
	
	if (argc > 0)
	{
		exec_path = argv[0];
		exec_path = exec_path.substr(0, exec_path.find_last_of('\\') + 1);
	}

	GR::ApplicationSettings Settings = { "Vulkan Application", {1024, 720} };
	std::unique_ptr<GR::GrayEngine> Engine = std::make_unique<GR::GrayEngine>(exec_path, Settings);

	Engine->AddInputFunction(Loop);
	Engine->GetEventListener().Subscribe(KeyPress);

	sword = Engine->LoadModel("content\\sword.fbx", nullptr);
	Engine->GetMainCamera().View.SetOffset({0.0, 0.0, -200.0});

	Engine->StartGameLoop();

	return 0;
}